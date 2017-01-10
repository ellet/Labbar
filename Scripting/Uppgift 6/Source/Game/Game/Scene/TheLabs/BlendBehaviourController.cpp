#include "stdafx.h"
#include "BlendBehaviourController.h"
#include "PollingStation.h"
#include "..\Behaviours\EvadeBehaviour.h"
#include "Unit.h"

const float myMaxSpeed = 100.f;

BlendBehaviourController::BlendBehaviourController(const Unit & aParentUnit) : Controller(aParentUnit), mySeekBehaviour(aParentUnit), myWanderBehaviour(aParentUnit), myEvadeBehaviour(aParentUnit)
{
	PollingStation::RegisterBlenderController(*this);

	//mySeekBehaviour.SetWeight(11.f);
	//myWanderBehaviour.SetWeight(7.f);
	//myEvadeBehaviour.SetWeight(10.f);

	SeekBehaviour::ourWeight = 1.f;
	WanderBehaviour::ourWeight = 7.f;
	EvadeBehaviour::ourMaxWeight = 10.f;
}


BlendBehaviourController::~BlendBehaviourController()
{
	PollingStation::UnRegisterBlenderController(*this);
}

SB::Vector2f BlendBehaviourController::GetDirection(const SB::Time & aDeltaTime)
{
	Steering currentSterring;
	currentSterring += myWanderBehaviour.GetSteering(aDeltaTime);
	currentSterring += mySeekBehaviour.GetSteering(aDeltaTime);
	currentSterring += myEvadeBehaviour.GetSteering(aDeltaTime);
	SB::Vector2f direction = currentSterring.Direction.GetNormalized();


	return direction * myMaxSpeed * currentSterring.SpeedPercentage;
}

void BlendBehaviourController::RecieveEvent(const SetSeekTargetEvent & aSeekTargetEvent)
{
	mySeekBehaviour.SetTargetPosition(aSeekTargetEvent.myTargetPosition);
}

void BlendBehaviourController::RecieveEvent(const PointToEvadeEvent & aEvadeEvent)
{
	myEvadeBehaviour.AddAvoidPosition(aEvadeEvent.myPointToEvade);
}

SB::CircleShape BlendBehaviourController::GetEvadeArea()
{
	return SB::CircleShape(myUnit->GetPosition(), myEvadeBehaviour.GetEvadeRadius());
}

SB::Vector2f BlendBehaviourController::GetFuturePosition(const float aTimeDelta)
{
	return myUnit->GetPosition() + (myUnit->GetSpeed() * aTimeDelta);
}
