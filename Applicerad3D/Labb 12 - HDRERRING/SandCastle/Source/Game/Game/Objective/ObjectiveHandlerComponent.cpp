#include "stdafx.h"
#include "ObjectiveHandlerComponent.h"
#include "ObjectiveComponent.h"

ObjectiveHandlerComponent::ObjectiveHandlerComponent()
{
	myText = nullptr;

	myText = std::make_shared<SB::Text>();

}


ObjectiveHandlerComponent::~ObjectiveHandlerComponent()
{
}

void ObjectiveHandlerComponent::RemoveObjective(ObjectiveComponent *aObjective)
{
	for (unsigned short i = 0; i < myObjectives.Size(); ++i)
	{
		if (myObjectives[i]->GetIdentity() == aObjective->GetIdentity())
		{
			myObjectives.RemoveAtIndex(i);
		}
	}
}

void ObjectiveHandlerComponent::ObjectiveComplete()
{
	*myText = SB::FormatString(myCurrentObjective->GetDescription(), *myCurrentObjective).c_str();
}

void ObjectiveHandlerComponent::AddObjective(ObjectiveComponent *aObjective)
{
	myObjectives.Add(aObjective);
}

void ObjectiveHandlerComponent::ActivateObjective(ObjectiveComponent *aObjective)
{
	
	myCurrentObjective = aObjective;
	*myText = SB::FormatString(aObjective->GetDescription(), *aObjective).c_str();

}

void ObjectiveHandlerComponent::LoadData(SB::DataNode aProperties)
{
	SB::DataNode objectiveList = aProperties["objectives"];
	myObjectiveNames.Reserve(static_cast<unsigned short> (objectiveList.Size()));
	for (unsigned short i = 0; i < static_cast<unsigned short> (objectiveList.Size()); ++i)
	{
		myObjectiveNames.Add(objectiveList[i].GetString());
	}
	myObjectives.Resize(myObjectiveNames.Size());
}

void ObjectiveHandlerComponent::Initialize()
{
	GetGameObject().GetScene().GetGUI()->GetGUIElement("ObjectiveGUI")->SetText(myText);
}

void ObjectiveHandlerComponent::Render() const
{
	myText->Render();
}
