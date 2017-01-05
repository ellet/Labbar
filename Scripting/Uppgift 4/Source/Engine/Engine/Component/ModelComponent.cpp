#include "stdafx.h"
#include "ModelComponent.h"
#include "Engine/Model/ModelInstance.h"
#include "Engine/Effect/Effect.h"
#include "Engine\Model\AssimpModel.h"
#include "Engine/GameObject/GameObject.h"

namespace SB
{
	ModelComponent::ModelComponent()
	{
		myColor = Vector4f::One;
		myDoAutomaticRendering = true;
		myLodCache = SIZE_MAX;
		myCullingCache = 0;
		myAnimationPlaybackData.animationIndex = 0;
		myAnimationPlaybackData.time = 0;
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

	void ModelComponent::Update(const Time& aDeltaTime)
	{
		myAnimationPlaybackData.time += aDeltaTime;
	}

	void ModelComponent::Render(const Camera & aCamera) const
	{
		if (myDoAutomaticRendering)
		{
			TriggerRender(aCamera);
		}
	}

	void ModelComponent::TriggerRender(const Camera & aCamera) const
	{
		if (myModel != nullptr && myModel->MakeReady(true) == true)
		{
			myModel->Render(aCamera, myEffect, GetFromWorldMatrix(), myPreviousToWorld, myColor, &myAnimationPlaybackData, const_cast<uint8_t*>(&myCullingCache), const_cast<size_t*>(&myLodCache));
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


	const std::string & ModelComponent::GetNameOfLastRenderedMesh() const
	{
		if (myLodCache != SIZE_MAX)
		{
			return myModel->GetMeshes()[myLodCache]->GetMeshName();
		}
		else if (myModel->GetMeshes().size() > 0)
		{
			return myModel->GetMeshes()[0]->GetMeshName();
		}

		return EmptyString;
	}

	void ModelComponent::GetNamesOfAllMeshes(GrowingArray<std::string> & aGrowingArraytoFill) const
	{
		const_cast<ModelComponent*>(this)->Prepare(false);

		std::vector<std::shared_ptr<GenericMesh>> meshes = myModel->GetMeshes();
		aGrowingArraytoFill.Resize(static_cast<unsigned short>( meshes.size()));

		for (unsigned short iMesh = 0; iMesh < aGrowingArraytoFill.Size(); ++iMesh)
		{
			aGrowingArraytoFill[iMesh] = meshes[static_cast<size_t>(iMesh)]->GetMeshName();
		}
	}

	void ModelComponent::DebugRender(const Camera & aCamera) const
	{
		if (ourRenderAxis == true)
		{
			Matrix44f testy = myObject->GetTransformation();
			Vector3f objectPos = testy.GetPosition();
			Quaternion objectRot = myObject->GetWorldRotation();
			float axisLength = GetBoundingBox().GetMaximumRadius();
			axisLength *= 1.3f;


		
			//Y axiz
			Engine::GetDebugDrawer().DrawLine(aCamera, objectPos, objectPos + objectRot.GetUpward() * axisLength, Vector4f(0.f, 1.f, 0.f, 1.f));
			//Z axis
			Engine::GetDebugDrawer().DrawLine(aCamera, objectPos, objectPos + objectRot.GetForward() * axisLength, Vector4f(0.f, 0.f, 1.f, 1.f));
			//X axis
			Engine::GetDebugDrawer().DrawLine(aCamera, objectPos, objectPos + objectRot.GetRight() * axisLength, Vector4f(1.f, 0.f, 0.f, 1.f));
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

	void ModelComponent::PlayAnimation(const char* aAnimationName)
	{
		myAnimationPlaybackData.time = 0.f;
		AssimpModel * m = dynamic_cast<AssimpModel*>(&*myModel);
		if (m != nullptr)
		{
			myAnimationPlaybackData.animationIndex = m->GetAnimationIndex(aAnimationName);
		}
	}

	void ModelComponent::ToJson(JsonSerializer &aSerializer) const
{
		if (myPath != "")
		{
			JsonSerializer &serializer = aSerializer;

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
