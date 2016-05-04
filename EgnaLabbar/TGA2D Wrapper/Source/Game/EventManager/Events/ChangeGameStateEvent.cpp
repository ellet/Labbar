#include "stdafx.h"
#include "ChangeGameStateEvent.h"
#include <StateManager/StateManager.h>


ChangeGameStateEvent::ChangeGameStateEvent(enumGameStates aGameState)
{
	myGameStateToChangeTo = aGameState;
}

ChangeGameStateEvent::~ChangeGameStateEvent()
{
}

void ChangeGameStateEvent::OneShotEvent()
{
	StateManager::SetActiveState(myGameStateToChangeTo);
}
