#include "stdafx.h"
#include "PlayerSetGotoEvent.h"
#include "../../../Game/Levels/LevelManager.h"


PlayerSetGotoEvent::PlayerSetGotoEvent(Vector2f aPositionToMoveToo)
{
	myPositionToMove = aPositionToMoveToo;
}

PlayerSetGotoEvent::~PlayerSetGotoEvent()
{

}

void PlayerSetGotoEvent::OneShotEvent()
{
	LevelManager::SetPlayerGotoPosition(myPositionToMove);
}