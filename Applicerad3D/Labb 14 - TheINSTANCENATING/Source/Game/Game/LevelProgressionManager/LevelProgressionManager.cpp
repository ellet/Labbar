#include "stdafx.h"
#include "LevelProgressionManager.h"
#include <Engine/Scene/Messages/CreateSceneMessage.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include "Game/Player/PlayerMessages.h"
#include "Game/GenericGameMessages.h"
#include "Game/Game.h"

LevelProgressionManager::LevelProgressionManager() : Subscriber<SB::EndOfFrameMessage>(10)
{
	myCurrentLevel = 0;
	LoadData();
}


LevelProgressionManager::~LevelProgressionManager()
{
}

SB::ReceiveResult LevelProgressionManager::Receive(const ProgressToNextLevelMessage & aMessage)
{
	//Remove this when LevelClearedScene/ScoreScreen exists.
	//Currently changes level in a flat way.

	myProgressToNextLevel = true;

	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult LevelProgressionManager::Receive(const SelectedLevelMessage & aMessage)
{
	if (aMessage.myLevelSelected > myLevelFilePaths.Size())
	{
		Error("Tried to select a level when we have no filepath for the level number! Is the number too high, or is the path not saved?");
	}

	myCurrentLevel = aMessage.myLevelSelected; //Note that this will be one number too large until next frame.
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, [=](std::shared_ptr<SB::Scene> scene)
	{

		if (mySavedPlayerData.find(myLevelFilePaths[aMessage.myLevelSelected]) != mySavedPlayerData.end())
		{
			auto binding = SB::PostMaster::Push(*scene);
			SB::PostMaster::Post(SetPlayerDataMessage(mySavedPlayerData[myLevelFilePaths[aMessage.myLevelSelected]]));
		}

	}, myLevelFilePaths[aMessage.myLevelSelected]));


	myCurrentSavedFile = myLevelFilePaths[myCurrentLevel];
	
	return SB::ReceiveResult::eContinue;
}


SB::ReceiveResult LevelProgressionManager::Receive(const SB::EndOfFrameMessage & aMessage) 
{
	if (myProgressToNextLevel == true )
	{
		myProgressToNextLevel = false;
		++myCurrentLevel;
		if (myCurrentLevel >= myLevelFilePaths.Size()) //Last level?
		{
			SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eToFirst)); //Let's go to main menu.
																			   //SB::PostMaster::Post(CreateSceneMessage(eSceneClass::eCredits, eSceneType::eSub)); //And queue credits. Which removes itself when done.
		}
		else
		{
			SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eMajor));
			SB::PostMaster::Post(OnSceneExitMessage(mySavedPlayerData[myLevelFilePaths[myCurrentLevel]]));
			myCurrentSavedFile = myLevelFilePaths[myCurrentLevel];
			SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, myLevelFilePaths[myCurrentLevel]));
		}
	}
	else if (myLoadLastSave == true)
	{
		myLoadLastSave = false;
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eMajor));
		SB::PostMaster::Post(OnSceneExitMessage(mySavedPlayerData[myLevelFilePaths[myCurrentLevel]]));
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, myCurrentSavedFile));
	}
	return SB::ReceiveResult::eContinue;

}

SB::ReceiveResult LevelProgressionManager::Receive(const ReloadToLastSaveMessage &aMessage)
{
	myLoadLastSave = true;
	return SB::ReceiveResult::eContinue;
}

SB::ReceiveResult LevelProgressionManager::Receive(const SaveLevelMessage &aMessage)
{
	myCurrentSavedFile = SB::Engine::GetJsonSerializer().GetSaveDataPath();
	return SB::ReceiveResult::eContinue;
}

void LevelProgressionManager::LoadData()
{
	SB::DataDocument doc;
	SB::Data::Open("Assets/Data/LevelsData/levelsData.json", doc);

	LoadLevelPaths(doc["filePaths"]);
	LoadPlayerData(doc["playerData"]);
}

void LevelProgressionManager::LoadLevelPaths(SB::DataNode aLevelPathsNode)
{
	for (unsigned short i = 0; i < aLevelPathsNode.Capacity(); ++i)
	{
		myLevelFilePaths.Add(aLevelPathsNode[i].GetString());
	}
}

void LevelProgressionManager::LoadPlayerData(SB::DataNode aPlayerDataNode)
{
	for (unsigned short i = 0; i < aPlayerDataNode.Capacity(); ++i)
	{
		SavedPlayerData data;
		data.myHealth = aPlayerDataNode[i]["startingHealth"].GetFloat();
		
		for (unsigned short j = 0; j < aPlayerDataNode[i]["ownedPrimaryWeapons"].Capacity(); j++)
		{
			data.myOwnedPrimaryWeapons.Add(aPlayerDataNode[i]["ownedPrimaryWeapons"][j].GetBool());
		}

		for (unsigned short j = 0; j < aPlayerDataNode[i]["ownedSecondaryWeapons"].Capacity(); j++)
		{
			data.myOwnedSecondaryWeapons.Add(aPlayerDataNode[i]["ownedSecondaryWeapons"][j].GetBool());
		}

		mySavedPlayerData[myLevelFilePaths[i]] = data;
		Game::GetInstance().GetPlayerSavedData() = data;
	}
}