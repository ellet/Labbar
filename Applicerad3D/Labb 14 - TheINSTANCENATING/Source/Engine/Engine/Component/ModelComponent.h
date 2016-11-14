#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Engine/BoundingBox.h>
#include "../GenericEngineMessages.h"


namespace ENGINE_NAMESPACE
{
	class Model;
	class Effect;

	class ModelComponent : public BaseComponent, public Subscriber<EndOfFrameMessage>
	{
	public:
		ModelComponent();
		~ModelComponent();

		bool Prepare(bool aLoadAsynchronously) override;

		virtual void Render() const override;
		void TriggerRender() const;

		void SetModel(std::shared_ptr<Model> aModel);

		void SetModel(const char* aModelFilePath);

		BoundingBoxf GetBoundingBox() const;

		virtual void Initialize() override;

		void SetMatrix(const Matrix44f & aMatrix);

		void SetEffect(const std::shared_ptr<Effect> & aEffect);
		const std::shared_ptr<Effect> & GetEffect() const;

		void LoadData(DataNode aProperties) override;
		void DisableAutomaticRender();
		

		virtual void DebugRender() const override;

		Matrix44f GetFromWorldMatrix() const;
		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;

		static void SwitchRenderAxisFlag();

		virtual void ToJson()const override;

	private:
		static bool ourRenderAxis;

		std::shared_ptr<Model> myModel;
		Matrix44f myMatrix;
		Matrix44f myPreviousToWorld;
		Vector4f myColor;
		std::shared_ptr<Effect> myEffect;

		std::string myPath;
		bool myDoAutomaticRendering;
	};
}
