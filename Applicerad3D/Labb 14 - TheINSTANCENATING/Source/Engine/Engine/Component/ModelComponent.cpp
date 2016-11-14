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
		myDoAutomaticRendering = true;
	}

	ModelComponent::~ModelComponent()
	{
	}

	bool ModelComponent::Prepare(bool aLoadAsynchronously)
	{
		if (myModel != nullptr)
		{
			return myModel->MakeReady(aLoadAsynchronously);
		}
		return true;
	}

	void ModelComponent::Render() const
	{
		if (myDoAutomaticRendering)
		{
			TriggerRender();
		}
	}

	void ModelComponent::TriggerRender() const
	{
		if (myModel != nullptr && myModel->MakeReady(true) == true)
		{
			myModel->Render(myEffect, GetFromWorldMatrix(), myPreviousToWorld, myColor);
		}
	}

	void ModelComponent::SetModel(std::shared_ptr<Model> aModel)
	{
		myModel = aModel;
	}

	void ModelComponent::SetModel(const char* aModelFilePath)
	{
		if (aModelFilePath == nullptr)
		{
			myPath = "";
			myModel = nullptr;
			return;
		}
		myPath = aModelFilePath;

		std::shared_ptr<AssimpModel> model = Engine::GetResourceManager().Get<AssimpModel>(myPath);
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
		myPreviousToWorld = GetFromWorldMatrix();
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
		if (std::string(aProperties["modelPath"].GetString()) == "")
		{
			Error("Model on object " + myObject->GetIdentifier() + " is unloadable. It does not seem to have a mesh. The assigned path is currently \"\".");
		}
		SetModel(aProperties["modelPath"].GetString());
		SetMatrix(Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * Matrix44f::CreateRotateAroundY(Pi));
	}

	void ModelComponent::DisableAutomaticRender()
	{
		myDoAutomaticRendering = false;
	}

	void ModelComponent::DebugRender() const
	{
		if (ourRenderAxis == true)
		{
			Matrix44f testy = myObject->GetTransformation();
			Vector3f objectPos = testy.GetPosition();
			Quaternion objectRot = myObject->GetWorldRotation();
			float axisLength = GetBoundingBox().GetMaximumRadius();
			axisLength *= 1.3f;


		
			//Y axiz
			Engine::GetDebugDrawer().DrawLine(objectPos, objectPos + objectRot.GetUpward() * axisLength, Vector4f(0.f, 1.f, 0.f, 1.f));
			//Z axis
			Engine::GetDebugDrawer().DrawLine(objectPos, objectPos + objectRot.GetForward() * axisLength, Vector4f(0.f, 0.f, 1.f, 1.f));
			//X axis
			Engine::GetDebugDrawer().DrawLine(objectPos, objectPos + objectRot.GetRight() * axisLength, Vector4f(1.f, 0.f, 0.f, 1.f));
		}
	}

	Matrix44f ModelComponent::GetFromWorldMatrix() const
	{
		return myMatrix * myObject->GetTransformation();
	}

	ReceiveResult ModelComponent::Receive(const EndOfFrameMessage & aMessage)
	{
		myPreviousToWorld = GetFromWorldMatrix();
		return ReceiveResult::eContinue;

	}

	void ModelComponent::ToJson() const
{
		if (myPath != "")
		{
			JsonSerializer &serializer = Engine::GetJsonSerializer();

			serializer.WriteObject("properties");
			serializer.WriteNode("modelPath", myPath);
			serializer.StepOut();
			serializer.WriteNode("type", "ModelComponent");
		}
		

	}
	void ModelComponent::SwitchRenderAxisFlag()
	{
		ourRenderAxis = !ourRenderAxis;
	}



	bool ModelComponent::ourRenderAxis = false;

}
