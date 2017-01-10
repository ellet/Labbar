#include "stdafx.h"

#include "ObjectiveComponent.h"
#include "ObjectiveHandlerComponent.h"
#include "Objective.h"
#include <Engine\Marker\MarkerComponent.h>
#include <Engine\GUI\GUIMarker.h>


namespace SB
{
	ObjectiveComponent::ObjectiveComponent()
	{

	}

	ObjectiveComponent::~ObjectiveComponent()
	{
	}


	const std::string & ObjectiveComponent::GetIdentity() const
	{
		return myIdentity;
	}

	const std::string & ObjectiveComponent::GetDescription() const
	{
		return myHandler->GetDescription(myChainAndPosition);
	}

	void ObjectiveComponent::SetCounter(unsigned short aCounter)
	{
		if (myHandler->SetCounter(myChainAndPosition, aCounter))
		{
			//OnObjectiveComplete();
		}
	}

	void ObjectiveComponent::IncrementCounter(unsigned short aIncrementValue)
	{
		if (myHandler->IncrementCounter(myChainAndPosition, aIncrementValue))
		{
			//OnObjectiveComplete();
		}
	}

	void ObjectiveComponent::DecrementCounter(unsigned short aDecrementValue)
	{
		if (myHandler->DecrementCounter(myChainAndPosition, aDecrementValue))
		{
			//OnObjectiveComplete();
		}
	}

	void ObjectiveComponent::Update(const Time & aDeltaTime)
	{
	}

	void ObjectiveComponent::AddObjectiveMarker()
	{

		ComponentPtr<MarkerComponent> marker = GetGameObject().CreateComponent<MarkerComponent>();
		marker->SetActive(false);
		//marker->Initialize();
		marker->SetColor(Vector4f(0.f, 1.f, 1.f, 1.f));
		marker->SetIsObjective(true);
		marker->SetSprite(myObjectiveType);

	}

	void ObjectiveComponent::Initialize()
	{


		SB::ObjectPtr sceneHandler = GetGameObject().GetScene().FindObject("SceneHandler");
		if (sceneHandler != nullptr)
		{
			myHandler = sceneHandler->GetComponent<ObjectiveHandlerComponent>();
			myChainAndPosition = myHandler->GetObjectiveChainAndPos(myIdentity.c_str());

			return;
		}
		Error("Did not find [SceneHandler]");
	}

	void ObjectiveComponent::LoadData(DataNode aProperties)
	{
		const char * identity = aProperties["identity"].GetString();
		if (aProperties.HasMember("objectiveType") == true)
		{
			ObjectiveType type = static_cast<ObjectiveType>(aProperties["objectiveType"].GetInt());
			myObjectiveType = type;
		}
		else
		{
			myObjectiveType = ObjectiveType::AttackObjective;
		}
		myIdentity = identity;
		AddObjectiveMarker();
	}

	ReceiveResult ObjectiveComponent::Receive(const ObjectiveStateChangedMessage &aMessage)
	{
		if (myHandler == nullptr)
		{
			ObjectPtr sceneHandler = GetGameObject().GetScene().FindObject("SceneHandler");
			if (sceneHandler == nullptr) Error("COULD NOT FIND SCENE HANDLER WHEN INITIALIZING");
			myHandler = sceneHandler->GetComponent<ObjectiveHandlerComponent>();
			if (myHandler == nullptr) Error("COULD NOT FIND OBJECTIVE HANDLER WHEN INITIALIZING");
			myChainAndPosition = myHandler->GetObjectiveChainAndPos(myIdentity.c_str());
		}

		if (aMessage.myObjective == myHandler->GetObjective(myChainAndPosition))
		{
			switch (aMessage.myState)
			{
			default:
				break;
			case eObjectiveState::eStarted:
				GetGameObject().GetComponent<MarkerComponent>()->SetActive(true);
				break;
			case eObjectiveState::eEnded:
				GetGameObject().GetComponent<MarkerComponent>()->SetActive(false);
				break;
			}
		}
		return SB::ReceiveResult::eContinue;
	}

	void ObjectiveComponent::ToJson(JsonSerializer &aSerializer) const
	{
		SB::JsonSerializer &serializer = aSerializer;
		serializer.WriteNode("type", "ObjectiveComponent");
		serializer.WriteObject("properties");
		serializer.WriteNode("identity", myIdentity);
		serializer.WriteNode("objectiveType", static_cast<int>(myObjectiveType));
		serializer.StepOut();
	}

	void ObjectiveComponent::OnObjectiveComplete()
	{

	}

};