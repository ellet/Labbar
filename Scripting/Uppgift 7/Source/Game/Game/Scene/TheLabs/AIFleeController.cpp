#include "stdafx.h"
#include "AIFleeController.h"
#include "Unit.h"
#include "PollingStation.h"


const float MaxSpeed = 345.f;
const float MinFleeSpeed = 25.f;

AIFleeController::AIFleeController(const Unit & aParentUnit) : Controller(aParentUnit)
{
	myFleeRadius = 250.f;
	myShouldFlee = false;
	//PollingStation::RegisterFleeController(*this);
}


AIFleeController::~AIFleeController()
{
	//PollingStation::UnRegisterFleeController(*this);
}

SB::Vector2f AIFleeController::GetDirection(const SB::Time & aDeltaTime)
{
	if (myShouldFlee == true)
	{
		const SB::Vector2f DifferenceVector = myUnit->GetPosition() - myFleeFromPosition;
		const float Distance = DifferenceVector.Length();

		float moreSpeed = (MaxSpeed - MinFleeSpeed) * (1.f - (Distance / myFleeRadius));
		float currentSpeed = MinFleeSpeed + moreSpeed;

		SB::Vector2f speedAndDirection = DifferenceVector.GetNormalized() * currentSpeed;

		if (Distance > myFleeRadius)
		{
			myShouldFlee = false;
		}
		else
		{
			return speedAndDirection;
		}
	}

	return SB::Vector2f::Zero;
}

SB::CircleShape AIFleeController::GetFleeArea() const
{
	return SB::CircleShape(myUnit->GetPosition(), myFleeRadius);
}

void AIFleeController::RecieveEvent(const SetFleeFromPositionEvent & aFleeEvent)
{
	myFleeFromPosition = aFleeEvent.myFleeFromPosition;
	myShouldFlee = true;
}

void AIFleeController::DebugRender(const SB::GuiRenderTarget & aRenderTarget) const
{
	//SB::Engine::GetDebugDrawer().DrawCircle(aRenderTarget, myUnit->GetPosition(), myFleeRadius);
}
