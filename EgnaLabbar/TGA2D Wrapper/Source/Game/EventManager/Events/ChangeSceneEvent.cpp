#include "stdafx.h"
#include "ChangeSceneEvent.h"
#include "../../Player/Player.h"
#include "../../Levels/LevelManager.h"
#include <iostream>

ChangeSceneEvent::ChangeSceneEvent(std::string &aTargetSceneName, Player &aPlayer,
	Vector2f &aTargetPosition)
{
	myTargetName = aTargetSceneName;
	myPlayer = &aPlayer;
	myTargetPosition = aTargetPosition;
	myName = "Change Scene Event";
}


ChangeSceneEvent::~ChangeSceneEvent()
{
}

void ChangeSceneEvent::OneShotEvent()
{
	std::cout << "OneShotEvent: Name: " << GetName() << std::endl;
	LevelManager::ChangeLevel(myTargetName);
}

