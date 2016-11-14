#include "stdafx.h"

#include "ObjectiveComponent.h"
#include "ObjectiveHandlerComponent.h"
#include "Objective.h"

ObjectiveComponent::ObjectiveComponent()
{

}

ObjectiveComponent::~ObjectiveComponent()
{
	// SB::ObjectPtr sceneHandler = GetGameObject().GetScene().FindObject("SceneHandler");
	// 
	// if (sceneHandler != nullptr)
	// {
	// 	//sceneHandler->GetComponent<ObjectiveHandlerComponent>()->RemoveObjective(this);
	// }
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

void ObjectiveComponent::Update(const SB::Time & aDeltaTime)
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void ObjectiveComponent::Render() const
{
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

void ObjectiveComponent::LoadData(SB::DataNode aProperties)
{
	const char * identity = aProperties["identity"].GetString();

	myIdentity = identity;
}

void ObjectiveComponent::ToJson() const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteNode("type", "ObjectiveComponent");
	serializer.WriteObject("properties");
	serializer.WriteNode("identity", myIdentity);
	serializer.StepOut();
}

void ObjectiveComponent::OnObjectiveComplete()
{
	
}

