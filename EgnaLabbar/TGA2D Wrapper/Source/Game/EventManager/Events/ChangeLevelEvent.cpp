#include "stdafx.h"
#include "ChangeLevelEvent.h"
#include "../../Player/Player.h"
#include "../../Levels/LevelManager.h"
#include <iostream>

ChangeLevelEvent::ChangeLevelEvent(std::string &aTargetSceneName, Player &aPlayer, Vector2f &aNewPlayerPosition)
{
	myTargetName = aTargetSceneName;
	myPlayer = &aPlayer;
	myName = "Change Scene Event";
	myNewPlayerPosition = aNewPlayerPosition;
}


ChangeLevelEvent::~ChangeLevelEvent()
{
}

void ChangeLevelEvent::OneShotEvent()
{
	LevelManager::ChangeLevel(myTargetName);
	
	//Set position and reset animation, etc. etc.
	myPlayer->SetPosition(myNewPlayerPosition);
	myPlayer->ResetGoto();

	//Simulate.
	myPlayer->Update(0.f);

}

