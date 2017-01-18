#include "stdafx.h"
#include "BaseController.h"
#include "Actors\Actor.h"


BaseController::BaseController(const Actor & aActor) : myActor(&aActor)
{
}

BaseController::~BaseController()
{
}

const SB::Vector2f BaseController::GetPosition() const
{
	return myActor->GetPosition();
}

const Actor & BaseController::GetActor() const
{
	return *myActor;
}
