#include "stdafx.h"
#include "AIComponent.h"
#include "ComponentIds.h"
#include "Ball.h"
#include "GameObject.h"

unsigned int CAIComponent::myID = EComponentIds_CAIComponent;

CAIComponent::CAIComponent()
	:myBall(nullptr)
{
}


CAIComponent::~CAIComponent()
{
}

void CAIComponent::Init(CBall* aBall)
{
	myBall = aBall;
}

void CAIComponent::Update(float /*aTimeDelta*/)
{
	if (!myBall)
	{
		return;
	}
	if (myBall->GetPosition().y + myBall->GetHeight() / 2 > myOwner->myPosition.y)
	{
		CComponentMessageOnInput inputMessage;
		inputMessage.myMovement = CComponentMessageOnInput::MOVE_DOWN;
		BroadcastMessage(&inputMessage);
	}
	else
	{
		CComponentMessageOnInput inputMessage;
		inputMessage.myMovement = CComponentMessageOnInput::MOVE_UP;
		BroadcastMessage(&inputMessage);
	}
}
