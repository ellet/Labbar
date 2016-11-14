#pragma once
#include "Player\PlayerDataStruct.h"

struct LevelClearedMessage
{
};




struct ProgressToNextLevelMessage
{

};

struct SelectedLevelMessage
{
	SelectedLevelMessage(const unsigned short aLevelSelected)
	{
		myLevelSelected = aLevelSelected;
	}

	unsigned short myLevelSelected;
};

struct OnSceneExitMessage
{
	OnSceneExitMessage(const SavedPlayerData & aLoadedPlayerData)
	{
		mySavedData = aLoadedPlayerData;
	}

	SavedPlayerData mySavedData;
};

