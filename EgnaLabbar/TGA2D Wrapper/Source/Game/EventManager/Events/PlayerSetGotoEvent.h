#pragma once
#include "Event.h"
#include <Vectors/vector2.h>

class PlayerSetGotoEvent : public Event
{
public:
	PlayerSetGotoEvent(Vector2f aPositionToMoveToo);
	~PlayerSetGotoEvent();

	void OneShotEvent() override;

private:
	Vector2f myPositionToMove;


};

