#pragma once
#include "Event.h"
#include <Vectors\Vector.h>
#include <string>

class Player;

class ChangeSceneEvent : public Event
{
public:
	ChangeSceneEvent(std::string &aTargetSceneName, Player &aPlayer, Vector2f &aTargetPosition);
	~ChangeSceneEvent();
	void OneShotEvent() override;
private:
	Player *myPlayer;
	Vector2f myTargetPosition;
	std::string myTargetName;
};

