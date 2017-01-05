#include "stdafx.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Texture\WorldRenderTexture.h"
#include "Engine/ParticleSystem/ParticleSystem.h"
#include "Skybox.h"
#include "Engine/Effect/SkyboxEffect.h"
#include "Engine/Model/ModelInstance.h"
#include "Engine/Texture/TextureCube.h"
#include "Engine/Component/ModelComponent.h"

namespace SB
{
	Camera::Camera(const char * aSkyboxPath /*= nullptr*/)
	{
		CreatePerspective(60.f, 16.f, 9.f, 0.1f, FAR_PLANE_DISTANCE);
		
		mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(nullptr));
		mySkybox->SetEffect(std::make_shared<SkyboxEffect>());

		Vector2ui renderResolution = Engine::GetRenderer().GetRenderTargetResolution().As<unsigned int>();
		myRenderTexture = std::make_shared<WorldRenderTexture>(renderResolution.x, renderResolution.y, true);

		SetSkybox(aSkyboxPath);
	}

	Camera::~Camera()
	{
	}

	void Camera::RenderScene(const Scene& aScene, const ParticleSystem * const aParticleSystem /*= nullptr*/)
	{
		GetRenderTexture()->Bind(0);

		if (mySkyboxTexture != nullptr)
		{
			myRenderTexture->GetModelRenderer().BindSkybox(mySkyboxTexture);
		}

		const std::shared_ptr<ComponentFactory<ModelComponent>> mcf = aScene.GetComponentFactory<ModelComponent>();
		if (mcf != nullptr)
		{
			GetRenderTexture()->GetModelRenderer().RenderShadowBuffer(0, *mcf);
		}
		  
		if (mySkybox != nullptr && mySkybox->Prepare(true) == true)
		{
			Vector3f oldPos = GetPosition();
			SetPosition(Vector3f::Zero);
			ApplyToVS();

			Engine::GetRenderer().DisableDepthWrite();
			mySkybox->InstantRender(*this);
			Engine::GetRenderer().EnableDepth();

			SetPosition(oldPos);
		}

		ApplyToVS();

		aScene.WithAllComponentFactories([this](const BaseComponentFactory & aComponentFactory)
		{
			aComponentFactory.Render(*this);
		});

		GetRenderTexture()->RenderBuffer();

		if (aParticleSystem != nullptr)
		{
			aParticleSystem->RenderWorldParticles(*this);
		}
	}

	void Camera::RenderBuffer()
	{
		myRenderTexture->GetModelRenderer().BindSkybox(mySkyboxTexture);
		GetRenderTexture()->RenderBuffer();
	}

	void Camera::CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane)
	{
		myProjection = Matrix44f::CreateProjection(aVerticalFoVInDegrees, aProjectionWidth, aProjectionHeight, aNearPlane, aFarPlane);
		myVerticalFieldOfView = DEGREES_TO_RADIANSF(aVerticalFoVInDegrees);
		Vector2f renderingSize = Engine::GetRenderer().GetRenderTargetResolution();
		myHorizontalFieldOfView = 2.f * atanf(tanf(myVerticalFieldOfView / 2.f) * (renderingSize.x / renderingSize.y));
	}
	
	void Camera::ApplyToVS() const
	{
		myRenderTexture->GetModelRenderer().SetCamera(myPosition, myRotation, myHorizontalFieldOfView, myVerticalFieldOfView);

		Engine::GetRenderer().SetCamera(GenerateCameraData());
	}

	CameraConstantBuffer Camera::GenerateCameraData() const
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		CameraConstantBuffer cameraData;
		cameraData.projection = myProjection;
		cameraData.view = rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		cameraData.view.Inverse();
		cameraData.cameraPosition = myPosition;

		cameraData.previousView = myPreviousView;
		cameraData.previousProjection = myPreviousProjection;

		return cameraData;
	}

	Vector2f Camera::WorldToScreen(const Vector3f& aWorldPosition) const
	{
		const_cast<Camera*>(this)->UpdateCache();

		Vector4f pos = Vector4f(aWorldPosition, 1.f) * myCachedViewProjection;
		pos /= pos.w;
		return Vector2f(pos.x, pos.y);
	}

	Vector3f Camera::ScreenToWorld(const Vector3f& aScreenPosition) const
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		CameraConstantBuffer cb;
		cb.projection = myProjection;
		cb.projection.Inverse();
		cb.view = rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		cb.cameraPosition = myPosition;

		Vector4f pos = Vector4f(aScreenPosition, 1.f) * cb.projection;
		pos /= pos.w;
		pos = Vector4f(pos, 1.f) * cb.view;
		return Vector3f(pos.x, pos.y, pos.z);
	}

	const Matrix44f& Camera::GetProjectionMatrix() const
	{
		return myProjection;
	}

	const Matrix44f Camera::GetTransformation() const
	{
		Matrix44f transformation = myRotation.GenerateMatrix();
		transformation.SetPosition(myPosition);
		return transformation;
	}
	
	ReceiveResult Camera::Receive(const EndOfFrameMessage & aMessage)
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		myPreviousView = rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		myPreviousView.Inverse();

		myPreviousProjection = myProjection;

		return ReceiveResult::eContinue;
	}

	ReceiveResult Camera::Receive(const WindowSizeChangedMessage& aMessage)
	{
		myRenderTexture = std::make_shared<WorldRenderTexture>(aMessage.myWidth, aMessage.myHeight, true);
		return ReceiveResult::eContinue;
	}

	const std::shared_ptr<WorldRenderTexture> & Camera::GetRenderTexture() const
	{
		return myRenderTexture;
	}

	void Camera::SetSkybox(const char* aSkyboxPath)
	{
		mySkyboxTexture = Engine::GetResourceManager().Get<TextureCube>(std::string(aSkyboxPath) == "" || aSkyboxPath == nullptr ? "Assets/Skyboxes/default.dds" : aSkyboxPath);
	}

	void Camera::UpdateCache()
	{
		if (myCachedPosition != myPosition || myCachedRotation != myRotation)
		{
			Quaternion rotation = myRotation;
			rotation.Normalize();
			auto rotationMatrix = rotation.GenerateMatrix();

			CameraConstantBuffer cb;
			cb.projection = myProjection;
			cb.view = rotationMatrix * Matrix44f::CreateTranslation(myPosition);
			cb.view.Inverse();
			cb.cameraPosition = myPosition;

			myCachedViewProjection = cb.view * cb.projection;

			myCachedPosition = myPosition;
			myCachedRotation = myRotation;
		}
	}

	void Camera::LookAt(const Vector3f & aLookAt)
	{
		Vector3f forwardVector = Vector3f(aLookAt - myPosition).GetNormalized();

		float dot = Vector3f::Dot(Vector3f(0.f, 0.f, 1.f), forwardVector);

		if (abs(dot - (-1.0f)) < 0.000001f)
		{
			myRotation = Quaternion(0.f, 1.f, 0.f, Pi);
			return;
		}
		if (abs(dot - (1.0f)) < 0.000001f)
		{
			myRotation = Quaternion();
			return;
		}

		float rotAngle = acosf(dot);
		Vector3f rotAxis = Vector3f::Cross(Vector3f(0.f, 0.f, 1.f), forwardVector);
		rotAxis.Normalize();
		myRotation = Quaternion();
		myRotation.RotateAlongAxis(rotAxis, rotAngle);
	}
}
