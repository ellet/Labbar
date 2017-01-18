#include "stdafx.h"
#include "BaseBehaviour.h"
#include "..\BaseController.h"


BaseBehaviour::BaseBehaviour(const BaseController & aController) : myController(&aController)
{

}

BaseBehaviour::~BaseBehaviour()
{
}

SB::Vector2f BaseBehaviour::GetPosition() const
{
	return myController->GetPosition();
}
