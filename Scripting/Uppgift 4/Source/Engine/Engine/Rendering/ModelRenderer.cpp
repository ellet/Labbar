#include "stdafx.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "..\Texture\TextureCube.h"
#include <Engine\Effect\StandardEffect.h>
#include "Engine/Lighting/PointLightComponent.h"
#include "..\Component\ModelComponent.h"

namespace SB
{

	ModelRenderer::ModelRenderer()
	{
		// Reserve identifier 0
		myMeshes.push_back(nullptr);
		myIsInstantRendering = false;

		myVertexBuffers.push_back(std::make_shared<VertexBuffer<InstanceData>>(nullptr, 1, false));
		myLightingBuffer = std::make_shared<ConstantBuffer<LightConstantBufferData>>();

		myLightingData.directionLight[0].color = Vector4f(1.f, 1.f, 1.f, 1.f);
		myLightingData.directionLight[0].direction = Vector4f(Vector3f(-1.f, -1.f, 1.f).GetNormalized(), 1.f);

		myLightingData.ambient = 1.0f;

		myCullingPlaneNormals.Resize(4);

		myEffect = std::make_shared<StandardEffect>();

		myShadowBuffer = std::make_shared<DepthBuffer>(256, 256);

		myAnimationBuffer = std::make_shared<ConstantBuffer<Matrix44f[64]>>();
		myAnimationEffect = std::make_shared<StandardEffect>("shaders/pbr/vertex_animation.fx");
	}

	ModelRenderer::~ModelRenderer()
	{
		// Empty rendering schedule hopefully releasing any shared pointers that are left to meshes
		for (size_t i = 0; i < myCurrentlyScheduledBatches.size(); i++)
		{
			myCurrentlyScheduledBatches[i]->FinishedRendering();
		}

		for (size_t i = 0; i < myMeshes.size(); i++)
		{
			if (myMeshes[i] != nullptr)
			{
				Engine::GetLogger().LogWarning("A mesh's identifier was never returned!");
			}
		}
	}

	void ModelRenderer::Render(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh, const InstanceData & aInstanceData, uint8_t * aCullingCache)
	{
		if (IsOutsideCullingFrustum(aMesh, aInstanceData.myMatrix, aCullingCache))
		{
			return;
		}

		size_t identifier = aMesh->GetIdentifier();
		if (identifier == 0)
		{
			Error("Mesh is missing batch identifier!");
		}
		if (identifier >= myMeshes.size())
		{
			myMeshes.resize(identifier + 1);
		}

		if (myMeshes[identifier] == nullptr)
		{
			myMeshes[identifier] = std::make_unique<BatchEntry>(aMesh);
		}

		myMeshes[identifier]->AddInstance(*this, aEffect == nullptr ? myEffect : aEffect, aInstanceData);
	}

	void ModelRenderer::RenderBuffer()
	{
		if (myCurrentlyScheduledBatches.size() == 0)
		{
			return;
		}

		RenderingEventGroup event(L"ModelRenderer::RenderBuffer()");

		if (mySkybox != nullptr)
		{
			mySkybox->BindToPS(6);
		}
		else
		{
			ID3D11ShaderResourceView * view[1] = { nullptr };
			Engine::GetRenderer().GetContext()->PSSetShaderResources(6, 1, view);
		}

		myIsInstantRendering = false;

		UpdateAndBindLightingBuffer();

		for (size_t i = 0; i < myCurrentlyScheduledBatches.size(); i++)
		{
			auto && matricesContainers = myCurrentlyScheduledBatches[i]->GetMatricesContainers();

			for (unsigned short  j = 0; j < matricesContainers.Size(); j++)
			{
				if (matricesContainers[j].effect == nullptr)
				{
					break;
				}

				const InstanceData * matrices = &matricesContainers[j].matrices[0];
				unsigned short matricesCount = matricesContainers[j].matrixCounter;

				auto vertexBuffer = myVertexBuffers[0];

				int c = 0;
				while (matricesCount >= vertexBuffer->GetCount())
				{
					c++;

					if (c >= static_cast<int>(myVertexBuffers.size()))
					{
						myVertexBuffers.push_back(std::make_shared<VertexBuffer<InstanceData>>(nullptr, myVertexBuffers.back()->GetCount() * 2, false));
					}

					vertexBuffer = myVertexBuffers[c];
				}

				vertexBuffer->UpdateData(matrices, matricesCount, false);
				vertexBuffer->Bind(1);
				myCurrentlyScheduledBatches[i]->GetMesh().RenderInstanced(matricesContainers[j].effect, matricesCount);
			}

			myCurrentlyScheduledBatches[i]->FinishedRendering();
		}

		myCurrentlyScheduledBatches.clear();
	}

	void ModelRenderer::Schedule(BatchEntry & aBatch)
	{
		myCurrentlyScheduledBatches.push_back(&aBatch);
	}

	void ModelRenderer::BindSkybox(const std::shared_ptr<TextureCube> & aSkybox)
	{
		myLightingData.myCubeMapMipMaps = aSkybox->GetMipMapLevels();
		mySkybox = aSkybox;
	}

	void ModelRenderer::SetBones(const std::vector<Matrix44f>& aBoneMatrices)
	{
		if (aBoneMatrices.size() > 64)
		{
			Error("Too many bones!");
		}
		Matrix44f data[64];
		memcpy(data, &aBoneMatrices[0], aBoneMatrices.size() * sizeof(Matrix44f));
		myAnimationBuffer->UpdateData(data);
	}

	const std::shared_ptr<Effect> & ModelRenderer::GetAnimationEffect()
	{
		return myAnimationEffect;
	}

	void ModelRenderer::SetEffect(const std::shared_ptr<Effect> &aEffect)
	{
		myEffect = aEffect;
	}

	void ModelRenderer::SetAmbient(float aAmbient)
	{
		myLightingData.ambient = aAmbient;
	}

	void ModelRenderer::SetDirectionalLight(int aIndex, const Vector3f & aLightDirection, const Vector4f & aLightColor)
	{
		myLightingData.directionLight[aIndex].direction = Vector4f(aLightDirection.GetNormalized(), 1.f);
		myLightingData.directionLight[aIndex].color = aLightColor;

		Matrix44f projection = Matrix44f::CreateScale(1.f / 1500.f, 1.f / 1500.f, 1.f / 10000.f);
		SB::Quaternion q;
		//q.RotateAroundLocalX(HalfPi);
		Vector2f topdownDelta = Vector2f(aLightDirection.x, aLightDirection.z);
		q = Quaternion::CreateFromVectors(Vector3f::Zero, aLightDirection, SB::Vector3f(0.f, 1.f, 0.f)) * q;
		Matrix44f view = q.GenerateMatrix() * SB::Matrix44f::CreateTranslation(myCameraPosition + SB::Vector3f(0.f, 0.f, -5000.f) * q);
		Matrix44f viewInverse = view.GetInverse();
		myLightingData.directionLight[aIndex].worldToLightSpace = viewInverse * projection;

		myDirectionalLightCameras[aIndex].view = viewInverse;
		myDirectionalLightCameras[aIndex].previousView = viewInverse;
		myDirectionalLightCameras[aIndex].projection = projection;
		myDirectionalLightCameras[aIndex].previousProjection = projection;
	}

	float ModelRenderer::GetAmbient() const
	{
		return myLightingData.ambient;
	}

	void ModelRenderer::RegisterLightComponent(const PointLightComponent& aPointLightComponent)
	{
		myPointLights.Add(&aPointLightComponent);
	}

	void ModelRenderer::RemoveLightComponent(const PointLightComponent& aPointLightComponent)
	{
		myPointLights.RemoveCyclic(&aPointLightComponent);
	}

	void ModelRenderer::SetCamera(const Vector3f& aPosition, const Quaternion& aRotation, const float aHorizontalFieldOfView, const float aVerticalFieldOfView)
	{
		myCameraPosition = aPosition;
		myCameraRotation = aRotation;

		Quaternion q;
		
		q = aRotation; q.RotateAroundLocalY(aHorizontalFieldOfView);
		myCullingPlaneNormals[0] = q.GetRight();
		q = aRotation; q.RotateAroundLocalY(-aHorizontalFieldOfView);
		myCullingPlaneNormals[1] = q.GetLeft();
		q = aRotation; q.RotateAroundLocalX(aVerticalFieldOfView);
		myCullingPlaneNormals[2] = q.GetDownward();
		q = aRotation; q.RotateAroundLocalX(-aVerticalFieldOfView);
		myCullingPlaneNormals[3] = q.GetUpward();
	}

	const std::shared_ptr<DepthBuffer> & ModelRenderer::GetShadowBuffer()
	{
		return myShadowBuffer;
	}

	void ModelRenderer::RenderShadowBuffer(int aDirectionalLightIndex, const ComponentFactory<ModelComponent> & aModelComponentFactory)
	{
		//SB::Engine::GetRenderer().GetModelRenderer().RenderBuffer();
		//
		myShadowBuffer->Clear();
		//
		//ID3D11RenderTargetView * views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
		//Engine::GetRenderer().GetContext()->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, views, myShadowBuffer->GetView());
		//Engine::GetRenderer().SetViewport(SB::Vector2f::Zero, myShadowBuffer->GetSize());
		//
		//SetDirectionalLightCamera(aDirectionalLightIndex);
		//
		//aModelComponentFactory.EnumerateActiveComponents([](ModelComponent & aComponent)
		//{
		//	aComponent.Render();
		//});
		//
		//Engine::GetRenderer().GetModelRenderer().RenderBuffer();
		//Engine::GetRenderer().GetImmediateBuffer()->Bind();
		myShadowBuffer->GetTexture()->BindToPS(7);
	}

	bool IsAbove(const Vector3f & aPointOnPlane, const Vector3f & aPlaneNormal, const Vector3f & aSphereCenter, const float aSphereRadius)
	{
		return Vector3f::Dot(aSphereCenter - aPointOnPlane, aPlaneNormal) >= aSphereRadius;
	}

	bool ModelRenderer::IsOutsideCullingFrustum(const std::shared_ptr<GenericMesh>& aMesh, const Matrix44f& aWorldMatrix, uint8_t * aCullingCache)
	{
		BoundingBoxf bb = aMesh->GetBoundingBox();
		bb.min = Vector4f(bb.min, 1.f) * aWorldMatrix;
		bb.max = Vector4f(bb.max, 1.f) * aWorldMatrix;
		
		const Vector3f center = bb.GetCenter();
		const float radius = bb.GetMaximumRadius();

		uint8_t cachedValue = UINT8_MAX;
		if (aCullingCache != nullptr)
		{
			cachedValue = *aCullingCache;

			if (IsAbove(myCameraPosition, myCullingPlaneNormals[cachedValue], center, radius) == true)
			{
				return true;
			}
		}

		for (uint8_t i=0; i<4; i++)
		{
			if (i == cachedValue)
			{
				continue;
			}

			if (IsAbove(myCameraPosition, myCullingPlaneNormals[i], center, radius) == true)
			{
				if (aCullingCache != nullptr)
				{
					*aCullingCache = i;
				}

				return true;
			}
		}

		return false;
	}

	void ModelRenderer::UpdateAndBindLightingBuffer()
	{
		memset(myLightingData.pointLight, 0, sizeof(myLightingData.pointLight));

		for (unsigned short lightIndex = 0 ; lightIndex < myPointLights.Size(); lightIndex++)
		{
			myLightingData.pointLight[lightIndex].position = myPointLights[lightIndex]->GetPosition();
			myLightingData.pointLight[lightIndex].radius = myPointLights[lightIndex]->GetRadius();
			myLightingData.pointLight[lightIndex].color = myPointLights[lightIndex]->GetColor();
			myLightingData.pointLight[lightIndex].intensity  = 1.f;
		}

		myLightingBuffer->UpdateData(myLightingData);
		myLightingBuffer->BindToPS(1);
	}

	void ModelRenderer::InstantRender(const std::shared_ptr<Effect>& aEffect, const std::shared_ptr<GenericMesh> & myMesh)
	{
		if (myIsInstantRendering == false)
		{
			Error("Instant rendering must be preceeded by calling ModelRenderer::PrepareInstantRender()");
		}

		myAnimationBuffer->BindToVS(2);
		myMesh->RenderInstanced(aEffect == nullptr ? myEffect : aEffect, 1);
	}

	void ModelRenderer::PrepareInstantRender(const InstanceData & aInstanceData)
	{
		myIsInstantRendering = true;

		myVertexBuffers[0]->UpdateData(&aInstanceData, 1, false);
		myVertexBuffers[0]->Bind(1);

		UpdateAndBindLightingBuffer();
	}

	void ModelRenderer::SetDirectionalLightCamera(const int aDirectionalLightIndex)
	{
		//SetCamera(myDirectionalLightCameras[aDirectionalLightIndex].cameraPosition, )
		Engine::GetRenderer().SetCamera(myDirectionalLightCameras[aDirectionalLightIndex]);
	}

	BatchEntry::BatchEntry(const std::shared_ptr<const GenericMesh> & aMesh)
	{
		myMesh = aMesh;
		myMeshScheduleLock = nullptr;
		myMatrices.Resize(2);
		for (unsigned short i = 0; i < myMatrices.Size(); i++)
		{
			myMatrices[i].matrices.Resize(16);
			myMatrices[i].matrixCounter = 0;
		}
		myEffectCounter = 0;
	}

	void BatchEntry::Schedule(ModelRenderer & aRenderer)
	{
		if (myMeshScheduleLock)
		{
			return;
		}
		myMeshScheduleLock = myMesh.lock();

		aRenderer.Schedule(*this);
	}

	bool BatchEntry::IsScheduled()
	{
		return myMeshScheduleLock != nullptr;
	}

	void BatchEntry::AddInstance(ModelRenderer & aRenderer, const std::shared_ptr<Effect> & aEffect, const InstanceData & aInstanceData)
	{
		if (myEffectCounter + 1 >= static_cast<int>(myMatrices.Size()))
		{
			unsigned short oldSize = myMatrices.Size();
			myMatrices.Resize(oldSize * 2);
			for (unsigned short i = oldSize; i < myMatrices.Size(); i++)
			{
				myMatrices[i].matrices.Resize(16);
				myMatrices[i].matrixCounter = 0;
			}
		}

		unsigned short effectIndex = static_cast<unsigned short>(myEffectCounter);

		for (short i = static_cast<short>(myEffectCounter) - 1; i >= 0; i--)
		{
			if (myMatrices[i].effect == aEffect)
			{
				effectIndex = static_cast<unsigned short>(i);
				return;
			}
		}

		auto && data = myMatrices[effectIndex];

		if (data.matrixCounter + 1 >= static_cast<int>(data.matrices.Size()))
		{
			data.matrices.Resize(static_cast<unsigned short>(data.matrices.Size() * 2));
		}

		data.matrices[data.matrixCounter++] = aInstanceData;

		if (data.effect == nullptr)
		{
			data.effect = aEffect;
		}

		Schedule(aRenderer);
	}

	void BatchEntry::FinishedRendering()
	{
		for (unsigned short i = 0; i < myMatrices.Size(); i++)
		{
			if (myMatrices[i].effect == nullptr)
			{
				break;
			}

			myMatrices[i].effect = nullptr;
			myMatrices[i].matrixCounter = 0;
		}

		myEffectCounter = 0;
		myMeshScheduleLock = nullptr;
	}

	const GrowingArray<BatchEntry::MatricesContainer> & BatchEntry::GetMatricesContainers() const
	{
		return myMatrices;
	}

	const GenericMesh & BatchEntry::GetMesh() const
	{
		if (myMeshScheduleLock == nullptr)
		{
			Error("Can only get the mesh of a scheduled batch entry!");
		}
		return *myMeshScheduleLock;
	}
}

