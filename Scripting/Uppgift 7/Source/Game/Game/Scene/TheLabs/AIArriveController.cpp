#include "stdafx.h"
#include "AIArriveController.h"
#include "PollingStation.h"
#include "Unit.h"


const float MaxSpeed = 750.f;
const float TimeToArrive = 0.15f;

AIArriveController::AIArriveController(const Unit & aParentUnit) : Controller(aParentUnit)
{
	//PollingStation::RegisterArriveController(*this);
	myTargetPosition = aParentUnit.GetPosition();

	myTargetRadius = 5.f;
	myStillNeedToMove = false;
}


AIArriveController::~AIArriveController()
{
}

void AIArriveController::RecieveEvent(const SetArriveTargetEvent & aEvent)
{
	myTargetPosition = aEvent.myTargetPosition;
}

SB::Vector2f AIArriveController::GetDirection(const SB::Time & aDeltaTime)
{
	SB::Vector2f targetOfSetVector = (myTargetPosition - myUnit->GetPosition());
	const float DistanceDiffernce = targetOfSetVector.Length();

	SB::Vector2f speedAndDirection = targetOfSetVector / TimeToArrive;

	if (speedAndDirection.Length() > MaxSpeed)
	{
		speedAndDirection = speedAndDirection.GetNormalized() * MaxSpeed;
	}

	if (DistanceDiffernce > myTargetRadius)
	{
		myStillNeedToMove = true;
		return speedAndDirection;
	}
	else
	{
		myStillNeedToMove = false;
	}


	return SB::Vector2f::Zero;
}



void AIArriveController::DebugRender(const SB::GuiRenderTarget & aRenderTarget) const
{
	SB::Engine::GetDebugDrawer().DrawCircle(aRenderTarget, myTargetPosition, myTargetRadius);
}
