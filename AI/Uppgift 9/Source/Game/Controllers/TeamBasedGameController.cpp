#include "stdafx.h"
#include "TeamBasedGameController.h"


const float MovementSpeed = 350.f;

TeamBasedGameController::TeamBasedGameController(const Actor & aActor) 
	: BaseController(aActor),
	mySeekBehaviour(*this)
{
}


TeamBasedGameController::~TeamBasedGameController()
{
}

void TeamBasedGameController::SetTargetPosition(const SB::Vector2f & aTargetPosition)
{
	mySeekBehaviour.SetTargetPosition(aTargetPosition);
}

SB::Vector2f TeamBasedGameController::Update(const float aDeltaTime)
{
	Steering output;
	output += mySeekBehaviour.UpdateSteering(aDeltaTime);

	return output.Direction * MovementSpeed * output.SpeedPercentage * aDeltaTime;
}
