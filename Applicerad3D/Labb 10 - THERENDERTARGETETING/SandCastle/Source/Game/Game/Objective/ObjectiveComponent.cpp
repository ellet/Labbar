#include "stdafx.h"

#include "ObjectiveComponent.h"
#include "ObjectiveHandlerComponent.h"


ObjectiveComponent::ObjectiveComponent()
{

}

ObjectiveComponent::~ObjectiveComponent()
{
	SB::ObjectPtr sceneHandler = GetGameObject().GetScene().FindObject("SceneHandler");

	if (sceneHandler != nullptr)
	{
		sceneHandler->GetComponent<ObjectiveHandlerComponent>()->RemoveObjective(this);
	}

}

const std::string & ObjectiveComponent::GetIdentity() const
{
	return myIdentity;
}

const std::string & ObjectiveComponent::GetDescription() const
{
	return myObjectiveDescription;
}

const std::string & ObjectiveComponent::GetObjectiveChain() const
{
	return myObjectiveChain;
}

void ObjectiveComponent::SetCounter(int aCounter)
{
	myCounter = aCounter;
	if (myCounter >= myCounterTarget)
	{
		SB::ObjectPtr sceneHandler = GetGameObject().GetScene().FindObject("SceneHandler");

		if (sceneHandler != nullptr)
		{
			sceneHandler->GetComponent<ObjectiveHandlerComponent>()->ObjectiveComplete();
		}
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
		sceneHandler->GetComponent<ObjectiveHandlerComponent>()->AddObjective(this);
		sceneHandler->GetComponent<ObjectiveHandlerComponent>()->ActivateObjective(this);
		return;
	}
	std::cout << "did not find scene handler" << std::endl;
}

void ObjectiveComponent::LoadData(SB::DataNode aProperties)
{
	myCounter = aProperties["counter"].GetInt();
	myCounterTarget = aProperties["target"].GetInt();
	myObjectiveDescription = aProperties["description"].GetString();
	myIdentity = aProperties["identity"].GetString();
	//myObjectiveChain = aProperties["objectiveChain"].GetString();
}

std::string ObjectiveComponent::ToString() const
{
	Error("Could not convert {[empty]} to a valid ObjectiveComponent value.");
}

std::string ObjectiveComponent::ToString(const std::string &aFormat) const
{
	if (aFormat == "counter")
	{
		return std::to_string(myCounter);
	}
	else if (aFormat == "target")
	{
		return std::to_string(myCounterTarget);
	}
	Error("Could not convert {" + aFormat + "} to a valid ObjectiveComponent value.");
}