#include "stdafx.h"
#include "ObjectiveHandlerComponent.h"
#include "ObjectiveComponent.h"
#include "Objective.h"

ObjectiveHandlerComponent::ObjectiveHandlerComponent()
{
	myText = nullptr;
	myText = std::make_shared<SB::Text>();
	
}


ObjectiveHandlerComponent::~ObjectiveHandlerComponent()
{
}

void ObjectiveHandlerComponent::ObjectiveComplete(const SB::Vector2us &aChainAndPos)
{
	std::shared_ptr<Objective> completedObjective = myObjectives[aChainAndPos.x][aChainAndPos.y];
	if (myObject->GetComponent<SB::LuaComponent>() != nullptr)
	{
		SB::PostMaster::Post(SaveLevelMessage());
		myObject->GetComponent<SB::LuaComponent>()->ReceiveLuaEvent("ObjectiveCompleteEvent", GetIdentity(aChainAndPos));
	}

	completedObjective->Deactivate();

	myObjectiveProgress[aChainAndPos.x]++;

	if (myObjectiveProgress[aChainAndPos.x] < myObjectives[aChainAndPos.x].Size())
	{
		std::shared_ptr<Objective> newObjective = myObjectives[aChainAndPos.x][myObjectiveProgress[aChainAndPos.x]];
		newObjective->Activate();
		*myText = SB::FormatString(newObjective->GetDescription(), *newObjective).c_str();
	}	
	else
	{
		*myText = "YOU FINISHED IT";
	}

}


const std::shared_ptr<Objective> & ObjectiveHandlerComponent::GetObjective(const SB::Vector2us &aChainAndPos)
{
	return myObjectives[aChainAndPos.x][aChainAndPos.y];
}

SB::Vector2us ObjectiveHandlerComponent::GetObjectiveChainAndPos(const char *aObjective)
{
	for (unsigned short i = 0; i < myObjectives.Size(); ++i)
	{
		for (unsigned short j = 0; j < myObjectives[i].Size(); ++j)
		{
			if (myObjectives[i][j]->GetIdentity() == aObjective)
			{
				return SB::Vector2us(i, j);
			}
		}
	}
	Error(SB::FormatString("The Objective {0} is not added to the SceneHandler's ObjectiveHandlerComponent", aObjective));
}

bool ObjectiveHandlerComponent::SetCounter(const SB::Vector2us &aChainAndPos, unsigned short aCounter)
{
	std::shared_ptr<Objective> objective = myObjectives[aChainAndPos.x][aChainAndPos.y];
	objective->SetCounter(aCounter);
	*myText = SB::FormatString(objective->GetDescription(), *objective).c_str();

	return CheckTargetReached(aChainAndPos);
	
}

bool ObjectiveHandlerComponent::IncrementCounter(const SB::Vector2us &aChainAndPos, unsigned short aIncrementValue)
{
	std::shared_ptr<Objective> objective = myObjectives[aChainAndPos.x][aChainAndPos.y];
	objective->IncrementCounter(aIncrementValue);
	*myText = SB::FormatString(objective->GetDescription(), *objective).c_str();
	return CheckTargetReached(aChainAndPos);

}

bool ObjectiveHandlerComponent::DecrementCounter(const SB::Vector2us &aChainAndPos, unsigned short aDecrementValue)
{
	std::shared_ptr<Objective> objective = myObjectives[aChainAndPos.x][aChainAndPos.y];
	objective->DecrementCounter(aDecrementValue);
	*myText = SB::FormatString(objective->GetDescription(), *objective).c_str();
	return CheckTargetReached(aChainAndPos);
}

const std::string & ObjectiveHandlerComponent::GetIdentity(const SB::Vector2us &aChainAndPos) const
{
	return myObjectives[aChainAndPos.x][aChainAndPos.y]->GetIdentity();
}

const std::string & ObjectiveHandlerComponent::GetDescription(const SB::Vector2us &aChainAndPos) const
{
	return myObjectives[aChainAndPos.x][aChainAndPos.y]->GetDescription();
}

void ObjectiveHandlerComponent::ActivateChain(unsigned short aChain)
{
	if (myObjectiveProgress[aChain] == -1)
	{
		myObjectiveProgress[aChain] = 0;
	}
	std::shared_ptr<Objective> objective = myObjectives[aChain][myObjectiveProgress[aChain]];
	objective->Activate();
	*myText = SB::FormatString(objective->GetDescription(), *objective).c_str();

}

void ObjectiveHandlerComponent::ActivateObjective(const char * aObjective)
{
	for (unsigned short i = 0; i < myObjectives.Size(); ++i)
	{
		for (unsigned short j = 0; j < myObjectives[i].Size(); ++j)
		{
			if (myObjectives[i][j]->GetIdentity() == aObjective)
			{
				myObjectives[i][j]->Activate();
				myObjectiveProgress[i] = j;
				*myText = SB::FormatString(myObjectives[i][j]->GetDescription(), *myObjectives[i][j]).c_str();
				return;
			}
		}
	}
	Error("Tried to activate objective with identifier " + std::string(aObjective) + ", which could not be found in the handler");
}

void ObjectiveHandlerComponent::LoadData(SB::DataNode aProperties)
{
	SB::DataNode objectiveChainsList = aProperties["objectiveChains"];
	myObjectives.Resize(static_cast<unsigned short> (objectiveChainsList.Size()));
	myObjectiveProgress.Resize(static_cast<unsigned short> (objectiveChainsList.Size()));

	for (unsigned short i = 0; i < static_cast<unsigned short> (objectiveChainsList.Size()); ++i)
	{
		myObjectiveProgress[i] = -1;
		if (objectiveChainsList[i].HasMember("currentObjective"))
		{
			myObjectiveProgress[i] = objectiveChainsList[i]["currentObjective"].GetShort();
		}
		SB::DataNode objectiveList = objectiveChainsList[i]["objectives"];
		myObjectives[i].Resize(static_cast<unsigned short> (objectiveList.Size()));

		for (unsigned short j = 0; j < static_cast<unsigned short> (objectiveList.Size()); ++j)
		{
			SB::Vector2us objectiveIndex(i, j);
			std::shared_ptr <Objective>objective = std::make_shared<Objective>(objectiveList[j], std::bind(&ObjectiveHandlerComponent::DefaultOnObjectiveComplete, this, objectiveIndex));
			myObjectives[i][j] = objective;
		}
	}
}

void ObjectiveHandlerComponent::Initialize()
{
	
	GetGameObject().GetScene().GetGUI()->GetGUIElement("ObjectiveGUI")->SetText(myText);
}

void ObjectiveHandlerComponent::Render() const
{
	myText->Render();

	for (unsigned short i = 0; i < myObjectives.Size(); ++i)
	{
		for (unsigned short j = myObjectiveProgress[i]; j < myObjectives[i].Size(); ++j)
		{
			if (myObjectives[i][j]->GetIsActive() == true)
			{
				myObjectives[i][j]->Render();
			}
		}
	}
}

void ObjectiveHandlerComponent::Update(const SB::Time & aDeltaTime)
{
	for(unsigned short i = 0; i < myObjectives.Size(); ++i)
	{
		for(unsigned short j = myObjectiveProgress[i]; j < myObjectives[i].Size(); ++j)
		{
			if (myObjectives[i][j]->GetIsActive() == true)
			{
				myObjectives[i][j]->Update(aDeltaTime);
			}
		}
	}

	while (myCompletedObjectives.Size() > 0)
	{
		ObjectiveComplete(myCompletedObjectives.GetLast());
		myCompletedObjectives.RemoveAtIndex(myCompletedObjectives.Size() - 1);
	}
}

void ObjectiveHandlerComponent::ToJson() const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteNode("type", "ObjectiveHandlerComponent");
	serializer.WriteObject("properties");

	serializer.WriteArray("objectiveChains");

	for (unsigned short iChain = 0; iChain < myObjectives.Size(); ++ iChain)
	{
		serializer.WriteObject();
		serializer.WriteNode("currentObjective", myObjectiveProgress[iChain]);


		serializer.WriteArray("objectives");
		for (unsigned short iObjective = 0; iObjective < myObjectives[iChain].Size(); ++iObjective)
		{
			serializer.WriteObject();
			serializer.WriteNode("identity", myObjectives[iChain][iObjective]->GetIdentity());
			serializer.WriteNode("description", myObjectives[iChain][iObjective]->GetDescription());
			serializer.WriteNode("counter", myObjectives[iChain][iObjective]->GetCounter());
			serializer.WriteNode("target", myObjectives[iChain][iObjective]->GetTarget());
			//TODO: serialize dialog chain & nodes
			serializer.StepOut();

		}
		serializer.StepOut();
		serializer.StepOut();
	}

	serializer.StepOut();
	serializer.StepOut();
}

bool ObjectiveHandlerComponent::CheckTargetReached(const SB::Vector2us & aChainAndPos)
{
	if (myObjectives[aChainAndPos.x][aChainAndPos.y]->TargetReached())
	{
		//This was moved to "DefaultOnObjectiveComplete" to ensure the objective dialog adds to completed objectives when done
		//myCompletedObjectives.Add(aChainAndPos);
		return true;
	}
	return false;
}

void ObjectiveHandlerComponent::DefaultOnObjectiveComplete(const SB::Vector2us& aChainAndPos)
{
	myCompletedObjectives.Add(aChainAndPos);
}
