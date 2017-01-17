#include "stdafx.h"
#include "Controller.h"
#include "AIEventHandler.h"
#include "Unit.h"


Controller::Controller(const Unit & aParentUnit) : myUnit(&aParentUnit)
{

}

Controller::~Controller()
{

}

SB::Vector2f Controller::GetDirection(const SB::Time & aDeltaTime)
{
	return myDirection;
}

const SB::Vector2f & Controller::GetPosition()
{
	return myUnit->GetPosition();
}

SB::Vector2f Controller::GetFuturePosition(const float aTimeDelta) const
{
	return myUnit->GetFuturePosition(aTimeDelta);
}

const Unit * Controller::GetUnit() const
{
	return myUnit;
}

void Controller::DebugRender(const SB::GuiRenderTarget & aRenderTarget) const
{

}
