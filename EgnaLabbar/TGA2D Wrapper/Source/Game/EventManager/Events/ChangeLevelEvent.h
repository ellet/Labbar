#pragma once
#include "Event.h"
#include <Vectors\Vector.h>
#include <string>

class Player;

class ChangeLevelEvent : public Event
{
public:
	ChangeLevelEvent(std::string &aTargetSceneName, Player &aPlayer, Vector2f &aNewPlayerPosition);
	~ChangeLevelEvent();
	void OneShotEvent() override;
private:
	Player *myPlayer;
	std::string myTargetName;
	Vector2f myNewPlayerPosition;
};

