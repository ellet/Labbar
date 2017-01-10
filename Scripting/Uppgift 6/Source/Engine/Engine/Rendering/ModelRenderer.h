#pragma once
#include "Engine\LightConstantBufferData.h"
#include "Engine\InstanceData.h"
#include "Engine\Camera\CameraConstantBuffer.h"

namespace SB
{
	class ModelRenderer;
	class PointLightComponent;

	class GenericMesh;
	template<typename T>
	class VertexBuffer;
	class ModelInstance;

	template <typename T>
	class ConstantBuffer;

	class Effect;

	class TextureCube;

	template <typename T>
	class ComponentFactory;

	class ModelComponent;

	class BatchEntry
	{
	public:
		BatchEntry(const std::shared_ptr<const GenericMesh> & aMesh);
		void Schedule(ModelRenderer & aRenderer);
		bool IsScheduled();

		void AddInstance(ModelRenderer & aRenderer, const std::shared_ptr<Effect> & aEffect, const InstanceData & aInstanceData);
		void FinishedRendering();

		struct MatricesContainer
		{
			GrowingArray<InstanceData> matrices;
			std::shared_ptr<Effect> effect;
			unsigned short matrixCounter;
		};

		const GrowingArray<MatricesContainer> & GetMatricesContainers() const;

		const GenericMesh & GetMesh() const;

	private:
		std::weak_ptr<const GenericMesh> myMesh;
		std::shared_ptr<const GenericMesh> myMeshScheduleLock;
		
		GrowingArray<MatricesContainer> myMatrices;
		int myEffectCounter;
	};

	class ModelRenderer
	{
	public:
		ModelRenderer();
		~ModelRenderer();

		void InstantRender(const std::shared_ptr<Effect>& aEffect, const std::shared_ptr<GenericMesh> & myMeshes);
		void Render(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh, const InstanceData & aInstanceData, uint8_t * aCullingCache = nullptr);
		
		void PrepareInstantRender(const InstanceData & aInstanceData);

		void Schedule(BatchEntry & aBatch);

		void SetEffect(const std::shared_ptr<Effect> &aEffect);
		void SetAmbient(float aAmbient);

		void SetDirectionalLight(int aIndex, const Vector3f & aLightDirection, const Vector4f & aLightColor);
		void SetDirectionalLightCamera(const int aDirectionalLightIndex);

		float GetAmbient() const;

		void RegisterLightComponent(const PointLightComponent& aPointLightComponent);
		void RemoveLightComponent(const PointLightComponent& aPointLightComponent);

		void SetCamera(const Vector3f& aPosition, const Quaternion& aRotation, const float aHorizontalFieldOfView, const float aVerticalFieldOfView);
		const Vector3f & GetCameraPosition() const;

		void RenderShadowBuffer(int aDirectionalLightIndex, const ComponentFactory<ModelComponent> & aModelComponentFactory);
		const std::shared_ptr<DepthBuffer> & GetShadowBuffer();

		void BindSkybox(const std::shared_ptr<TextureCube>& aSkybox);

		void SetBones(const std::vector<Matrix44f> & aBoneMatrices);
		const std::shared_ptr<Effect> & GetAnimationEffect();

	private:
		friend class WorldRenderTexture;
		void RenderBuffer();

		bool IsOutsideCullingFrustum(const std::shared_ptr<GenericMesh>& aMesh, const Matrix44f& aWorldMatrix, uint8_t * aCullingCache);
		void UpdateAndBindLightingBuffer();

		std::vector<BatchEntry*> myCurrentlyScheduledBatches;
		std::vector<std::unique_ptr<BatchEntry>> myMeshes;
		std::vector<std::shared_ptr<VertexBuffer<InstanceData>>> myVertexBuffers;
		GrowingArray<const PointLightComponent*> myPointLights;

		GrowingArray<Vector3f, uint8_t> myCullingPlaneNormals;
		Vector3f myCameraPosition;
		Quaternion myCameraRotation;

		std::shared_ptr<ConstantBuffer<LightConstantBufferData>> myLightingBuffer;
		LightConstantBufferData myLightingData;

		std::shared_ptr<Effect> myEffect;

		std::shared_ptr<ConstantBuffer<Matrix44f[64]>> myAnimationBuffer;
		std::shared_ptr<Effect> myAnimationEffect;

		bool myIsInstantRendering;
		std::array<CameraConstantBuffer, 1> myDirectionalLightCameras;
		std::shared_ptr<SB::DepthBuffer> myShadowBuffer;
		std::shared_ptr<TextureCube> mySkybox;
	};

	inline const Vector3f & ModelRenderer::GetCameraPosition() const
	{
		return myCameraPosition;
	}
}
