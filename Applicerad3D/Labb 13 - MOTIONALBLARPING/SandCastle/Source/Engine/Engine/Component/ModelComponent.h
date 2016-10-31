#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Engine/BoundingBox.h>


namespace ENGINE_NAMESPACE
{
	class Model;
	class Effect;

	class ModelComponent : public BaseComponent
	{
	public:
		ModelComponent();
		~ModelComponent();

		virtual void Render() const override;

		void SetModel(std::shared_ptr<Model> aModel);

		void SetModel(const char* aModelFilePath);

		BoundingBoxf GetBoundingBox() const;

		virtual void Initialize() override;

		void SetMatrix(const Matrix44f & aMatrix);

		void SetEffect(const std::shared_ptr<Effect> & aEffect);
		const std::shared_ptr<Effect> & GetEffect() const;

		void LoadData(DataNode aProperties) override;

		virtual void Update(const Time & aDeltaTime) override;

	private:
		std::shared_ptr<Model> myModel;
		Matrix44f myMatrix;
		Matrix44f myOldWorld;

		Vector4f myColor;
		std::shared_ptr<Effect> myEffect;
	};
}
