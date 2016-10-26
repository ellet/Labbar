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
		myColor = Vector4f::One;
	}

	ModelComponent::~ModelComponent()
	{
	}

	void ModelComponent::Render() const
	{
		if (strncmp(myObject->GetIdentifier().c_str(), "Shot", 4) == 0)
		{
			int c = 0;
			c++;
		}
		myModel->Render(myEffect, myMatrix * myObject->GetTransformation(), myColor);
	}

	void ModelComponent::SetModel(std::shared_ptr<Model> aModel)
	{
		myModel = aModel;
	}

	void ModelComponent::SetModel(const char* aModelFilePath)
	{
		std::shared_ptr<AssimpModel> model = Engine::GetResourceManager().Get<AssimpModel>(aModelFilePath);
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

	void ModelComponent::LoadData(DataNode aProperties)
	{
		SetModel(aProperties["modelPath"].GetString());
		SetMatrix(Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * Matrix44f::CreateRotateAroundY(Pi));
	}
}
