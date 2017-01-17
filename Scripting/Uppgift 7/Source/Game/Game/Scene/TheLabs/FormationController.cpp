#include "stdafx.h"
#include "FormationController.h"
#include "FormationGroup.h"
#include "Unit.h"
#include "PollingStation.h"

const float myMaxSpeed = 200.f;

FormationController::FormationController(const Unit & aParentUnit, FormationGroup & aGroup) : Controller(aParentUnit), myEvadeBehaviour(aParentUnit), mySeekBehaviour(aParentUnit), myGroup(&aGroup)
{
	myFormationIndex = myGroup->AddUnitToGroup();
	myGroup->SetOffset(myUnit->GetRadius() + 75.f);

	PollingStation::RegisterFormationController(*this);
}


FormationController::~FormationController()
{
	PollingStation::UnRegisterFormationController(*this);
}

SB::Vector2f FormationController::GetDirection(const SB::Time & aDeltaTime)
{
	mySeekBehaviour.SetTargetPosition(myGroup->GetPositionInFormation(myFormationIndex));

	Steering currentSterring;
	currentSterring += mySeekBehaviour.GetSteering(aDeltaTime);
	currentSterring += myEvadeBehaviour.GetSteering(aDeltaTime);

	return currentSterring.Direction.GetNormalized() * myMaxSpeed * currentSterring.SpeedPercentage;
}

void FormationController::RecieveEvent(const PointToEvadeEvent & aEvadeEvent)
{
	myEvadeBehaviour.AddAvoidPosition(aEvadeEvent.myPointToEvade);
}

SB::CircleShape FormationController::GetEvadeArea()
{
	return SB::CircleShape(myUnit->GetPosition(), myEvadeBehaviour.GetEvadeRadius());
}

void FormationController::DebugRender(const SB::GuiRenderTarget & aRenderTarget) const
{
	
}
