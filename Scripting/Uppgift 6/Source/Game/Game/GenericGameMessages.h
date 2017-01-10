#pragma once

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
	OnSceneExitMessage()
	{
	}
};

