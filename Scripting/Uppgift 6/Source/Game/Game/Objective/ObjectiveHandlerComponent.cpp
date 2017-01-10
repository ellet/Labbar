#include "stdafx.h"
#include "ObjectiveHandlerComponent.h"
#include "ObjectiveComponent.h"
#include "Objective.h"
#include "ObjectiveMessages.h"
#include "..\Engine\Engine\GUI\SpriteGUIElement.h"

namespace SB
{

	ObjectiveHandlerComponent::ObjectiveHandlerComponent()
	{
		myText = nullptr;
		myText = std::make_shared<SB::Text>(true);

		myText->SetFont(SB::Engine::GetInstance().GetResourceManager().Get<SB::Font>("Assets\\Text\\RECHARGEFONT"));
		myText->SetScale(SB::Vector2f(2.5f, 3.f));


		myText->SetColor(SB::Vector4f(1.f, 1.f, 1.f, 1.f));

		myText->SetCharactersPerSecond(20.f);
	}

	ObjectiveHandlerComponent::~ObjectiveHandlerComponent()
	{

	}

	void ObjectiveHandlerComponent::ObjectiveComplete(const SB::Vector2us &aChainAndPos)
	{
		std::shared_ptr<Objective> completedObjective = myObjectives[aChainAndPos.x][aChainAndPos.y];

		completedObjective->Deactivate();
		myObjectiveProgress[aChainAndPos.x]++;

		ObjectiveStateChangedMessage message;									 //
		message.myObjective = myObjectives[aChainAndPos.x][aChainAndPos.y];		  //
		message.myState = eObjectiveState::eEnded;								   //Post both to object and to all objectiveComponents
		myObject->TriggerEvent(message);										  //
		SB::PostMaster::Post(message);											 //

		if (myObjectiveProgress[aChainAndPos.x] < myObjectives[aChainAndPos.x].Size())
		{
			std::shared_ptr<Objective> newObjective = myObjectives[aChainAndPos.x][myObjectiveProgress[aChainAndPos.x]];

			message.myObjective = newObjective;										  //
			message.myState = eObjectiveState::eStarted;							   //Post both to object and to all objectiveComponents
			myObject->TriggerEvent(message);										  //
			SB::PostMaster::Post(message);											 //
			SB::PostMaster::Post(SaveLevelMessage());

			newObjective->Activate();
			*myText = SB::FormatString(newObjective->GetDescription(), *newObjective).c_str();
		}
		else
		{
			*myText = "Objective finished!";
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

		if (objective->GetIsActive() == true)
		{
			bool isAlreadyCompleted = objective->GetIsCompleted();

			if (isAlreadyCompleted == false)
			{
				objective->SetCounter(aCounter);
				*myText = SB::FormatString(objective->GetDescription(), *objective).c_str();
			}

		}

		return CheckTargetReached(aChainAndPos);

	}

	bool ObjectiveHandlerComponent::IncrementCounter(const SB::Vector2us &aChainAndPos, unsigned short aIncrementValue)
	{
		return SetCounter(aChainAndPos, myObjectives[aChainAndPos.x][aChainAndPos.y]->GetCounter() + aIncrementValue);
	}

	bool ObjectiveHandlerComponent::DecrementCounter(const SB::Vector2us &aChainAndPos, unsigned short aDecrementValue)
	{
		return SetCounter(aChainAndPos, myObjectives[aChainAndPos.x][aChainAndPos.y]->GetCounter() - aDecrementValue);
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

		ObjectiveStateChangedMessage message;									 //
		message.myObjective = objective;											//
		message.myState = eObjectiveState::eStarted;								   //Post both to object and to all objectiveComponents
		myObject->TriggerEvent(message);										  //
		SB::PostMaster::Post(message);											 //


		//*myText = "hej pa dig du din lille filur ja. nu far du ta och ge dig.";
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
					if (myObjectiveProgress[i] >= j)
					{
						return;
					}
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

			SB::DataNode objectiveList = objectiveChainsList[i]["objectives"];
			myObjectives[i].Resize(static_cast<unsigned short> (objectiveList.Size()));

			for (unsigned short j = 0; j < static_cast<unsigned short> (objectiveList.Size()); ++j)
			{
				SB::Vector2us objectiveIndex(i, j);
				std::shared_ptr<Objective> objective = std::make_shared<Objective>(objectiveList[j], std::bind(&ObjectiveHandlerComponent::DefaultOnObjectiveComplete, this, objectiveIndex));
				myObjectives[i][j] = objective;
			}
			myObjectiveProgress[i] = -1;
			if (objectiveChainsList[i].HasMember("currentObjective"))
			{
				myObjectiveProgress[i] = objectiveChainsList[i]["currentObjective"].GetShort();
			}
		}
	}

	void ObjectiveHandlerComponent::Initialize()
	{
		myObjectiveGUI = GetGameObject().GetScene().GetGUI()->GetGUIElement<SB::GUIElement>("ObjectiveGUI");
		//myText->SetPositionTopLeft(SB::Vector2f(0.f, 0.f));

		bool objectivesActive = false;
		for (unsigned short i = 0; i < myObjectives.Size(); ++i)
		{
			short j = myObjectiveProgress[i];

			if (j > 0)
			{
				objectivesActive = true;

				std::shared_ptr<Objective> completedObjective = myObjectives[i][j - 1];

				for (unsigned short iPreviousObjective = 0; iPreviousObjective < j; iPreviousObjective++)
				{
					myObjectives[i][iPreviousObjective]->Deactivate();
				}

				completedObjective->Deactivate();

				ObjectiveStateChangedMessage message;									 //
				message.myObjective = myObjectives[i][j - 1];		  //
				message.myState = eObjectiveState::eEnded;								   //Post both to object and to all objectiveComponents
				myObject->TriggerEvent(message);										  //
				SB::PostMaster::Post(message);


				if (j < myObjectives[i].Size())
				{
					std::shared_ptr<Objective> newObjective = myObjectives[i][j];
					//
					message.myObjective = newObjective;										  //
					message.myState = eObjectiveState::eStarted;							   //Post both to object and to all objectiveComponents
					myObject->TriggerEvent(message);										  //
					SB::PostMaster::Post(message);

					newObjective->Activate();
					*myText = SB::FormatString(newObjective->GetDescription(), *newObjective).c_str();
				}

			}
		}
		if (objectivesActive == false)
		{
			ActivateChain(0);
		}


		myObject->GetScene().GetGUI()->GetGUIElement<SB::GUIElement>("WarpPrompt")->SetActive(false);
	}

	void ObjectiveHandlerComponent::Render(const Camera & aCamera) const
	{
		//myText->Render();

		for (unsigned short i = 0; i < myObjectives.Size(); ++i)
		{
			for (unsigned short j = myObjectiveProgress[i]; j < myObjectives[i].Size(); ++j)
			{
				if (myObjectives[i][j]->GetIsActive() == true)
				{
					myObjectives[i][j]->Render(aCamera);
				}
			}
		}
	}
	//{myArray=0x000001c09ab0e220 {1} mySafeModeFlag=true myCapacity=2 ...}
	void ObjectiveHandlerComponent::Update(const SB::Time & aDeltaTime)
	{
		//myText->SetPositionBottomLeft(myText->GetPosition() + SB::Vector2f(1.f, 1.f) * aDeltaTime.InSeconds());
		//myObjectiveGUI->RefreshText();



		for (unsigned short i = 0; i < myObjectives.Size(); ++i)
		{
			for (unsigned short j = myObjectiveProgress[i]; j < myObjectives[i].Size(); ++j)
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

	bool ObjectiveHandlerComponent::GetIsActive(const SB::Vector2us &aChainAndPosition) const
	{
		return myObjectives[aChainAndPosition.x][aChainAndPosition.y]->GetIsActive() == true;
	}

	void ObjectiveHandlerComponent::ToJson(JsonSerializer &aSerializer) const
	{
		SB::JsonSerializer &serializer = aSerializer;

		serializer.WriteNode("type", "ObjectiveHandlerComponent");
		serializer.WriteObject("properties");

		serializer.WriteArray("objectiveChains");

		for (unsigned short iChain = 0; iChain < myObjectives.Size(); ++iChain)
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
		return myObjectives[aChainAndPos.x][aChainAndPos.y]->GetIsCompleted();
	}

	void ObjectiveHandlerComponent::DefaultOnObjectiveComplete(const SB::Vector2us& aChainAndPos)
	{
		myCompletedObjectives.Add(aChainAndPos);

		if (aChainAndPos.y >= myObjectives[aChainAndPos.x].Size() - 1)
		{
			SB::Engine::GetSoundManager().PostEvent("Play_MissionComplete");
		}
		else
		{
			SB::Engine::GetSoundManager().PostEvent("Play_ObjectiveComplete");
		}
	}
};