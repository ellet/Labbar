#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Engine/BoundingBox.h>
#include "../GenericEngineMessages.h"
#include "Engine/Animation/AnimationPlaybackData.h"


namespace SB
{
	class Model;
	class Effect;

	class ModelComponent : public BaseComponent, public Subscriber<EndOfFrameMessage>
	{
	public:
		ModelComponent();
		~ModelComponent();

		bool Prepare(bool aLoadAsynchronously) override;

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render(const Camera & aCamera) const override;
		void TriggerRender(const Camera & aCamera) const;

		void SetModel(std::shared_ptr<Model> aModel);

		void SetModel(const char* aModelFilePath);

		BoundingBoxf GetBoundingBox() const;

		virtual void Initialize() override;

		void SetMatrix(const Matrix44f & aMatrix);

		void SetEffect(const std::shared_ptr<Effect> & aEffect);
		const std::shared_ptr<Effect> & GetEffect() const;

		void LoadData(DataNode aProperties) override;
		void DisableAutomaticRender();
		
		const std::string & GetNameOfLastRenderedMesh() const;
		void GetNamesOfAllMeshes(GrowingArray<std::string> & aGrowingArraytoFill) const;

		virtual void DebugRender(const Camera & aCamera) const override;

		Matrix44f GetFromWorldMatrix() const;
		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;

		void PlayAnimation(const char * aAnimationName);

		static void SwitchRenderAxisFlag();

		virtual void ToJson(JsonSerializer &aSerializer)const override;

		_inline const Color & GetColor()
		{
			return myColor;
		}

		_inline void SetColor(const Color & aColor)
		{
			myColor = aColor;
		}

	private:
		static bool ourRenderAxis;

		std::shared_ptr<Model> myModel;
		Matrix44f myMatrix;
		Matrix44f myPreviousToWorld;
		Color myColor;
		std::shared_ptr<Effect> myEffect;

		std::string myPath;
		bool myDoAutomaticRendering;
		uint8_t myCullingCache;
		size_t myLodCache;
		AnimationPlaybackData myAnimationPlaybackData;
	};
}
