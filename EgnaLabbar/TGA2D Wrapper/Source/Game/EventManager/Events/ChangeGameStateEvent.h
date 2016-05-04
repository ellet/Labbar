#pragma once
#include "Event.h"

#include <StateManager/StatesEnum.h>

class ChangeGameStateEvent : public Event
{
public:
	ChangeGameStateEvent(enumGameStates aGameState);
	~ChangeGameStateEvent();

	void OneShotEvent() override;

private:
	enumGameStates myGameStateToChangeTo;
};

