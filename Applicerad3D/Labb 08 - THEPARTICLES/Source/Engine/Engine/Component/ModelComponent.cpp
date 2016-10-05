#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"
#include "Engine/Effect/Effect.h"
#include "Engine\Model\AssimpModel.h"
#include "Engine/GameObject/GameObject.h"

namespace ENGINE_NAMESPACE
{
	ModelComponent::ModelComponent()
	{
	}

	ModelComponent::~ModelComponent()
	{
	}

	void ModelComponent::Update(const Time & aDeltaTime)
	{
	}

	void ModelComponent::Render() const
	{
		myModel->Render(myEffect, myMatrix * myObject->GetTransformation());
	}

	void ModelComponent::SetModel(std::shared_ptr<Model> aModel)
	{
		myModel = aModel;
	}

	void ModelComponent::SetModel(const char* aModelFilePath)
	{
		std::shared_ptr<AssimpModel> model = std::make_shared<AssimpModel>(aModelFilePath);
		myModel = model;
	}

	BoundingBoxf ModelComponent::GetBoundingBox() const
	{
		SB::Matrix44f m = myMatrix * myObject->GetTransformation();
		BoundingBoxf bb =  myModel->GetBoundingBox();
		bb.min = Vector4f(bb.min, 1.f) * m;
		bb.max = Vector4f(bb.max, 1.f) * m;
		return bb;
	}

	void ModelComponent::Initialize()
	{
	}

	void ModelComponent::SetMatrix(const Matrix44f & aMatrix)
	{
		myMatrix = aMatrix;
	}

	void ModelComponent::SetEffect(const std::shared_ptr<Effect> & aEffect)
	{
		myEffect = aEffect;
	}

	const std::shared_ptr<Effect> & ModelComponent::GetEffect() const
	{
		return myEffect;
	}
}
