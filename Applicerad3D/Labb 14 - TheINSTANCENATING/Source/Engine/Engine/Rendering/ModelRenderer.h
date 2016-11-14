#pragma once
#include "Engine\LightConstantBufferData.h"
#include "Engine\InstanceData.h"

namespace ENGINE_NAMESPACE
{
	class PointLightComponent;

	class GenericMesh;
	template<typename T>
	class VertexBuffer;
	class ModelInstance;

	template <typename T>
	class ConstantBuffer;

	class Effect;

	class TextureCube;
	
	class BatchEntry
	{
	public:
		BatchEntry(const std::shared_ptr<const GenericMesh> & aMesh);
		void Schedule();
		bool IsScheduled();

		void AddInstance(const std::shared_ptr<Effect> & aEffect, const InstanceData & aInstanceData);
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
		void Render(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<GenericMesh> & aMesh, const InstanceData & aInstanceData);
		void RenderBuffer();

		void PrepareInstantRender(const InstanceData & aInstanceData);

		void Schedule(BatchEntry & aBatch);

		size_t GenerateBatchIdentifier(const std::shared_ptr<GenericMesh> & aMesh);
		void ReturnBatchIdentifier(size_t aBatchIdentifier);

		void SetSkyBox();

		void SetEffect(const std::shared_ptr<Effect> &aEffect);
		void SetAmbient(float aAmbient);
		void SetDirectionalLight(int aIndex, const Vector3f & aLightDirection, const Vector4f & aLightColor);

		float GetAmbient() const;

		void RegisterLightComponent(const PointLightComponent& aPointLightComponent);
		void RemoveLightComponent(const PointLightComponent& aPointLightComponent);

		void SetSkyBox(const std::string & aFilePath);

	private:
		std::vector<BatchEntry*> myCurrentlyScheduledBatches;
		std::vector<std::unique_ptr<BatchEntry>> myMeshes;
		std::stack<size_t> myReturnedBatchIdentifiers;
		std::vector<std::shared_ptr<VertexBuffer<InstanceData>>> myVertexBuffers;
		GrowingArray<const PointLightComponent*> myPointLights;

		std::shared_ptr<ConstantBuffer<LightConstantBufferData>> myLightingBuffer;
		LightConstantBufferData myLightingData;

		std::shared_ptr<TextureCube> mySkybox;
		std::shared_ptr<Effect> myEffect;

		bool myIsInstantRendering;
		void UpdateAndBindLightingBuffer();
	};

}
