#include "stdafx.h"
#include "PlayerController.h"


const float PlayerSpeed = 250.f;


PlayerController::PlayerController(const Actor & aActor) : BaseController(aActor)
{
}


PlayerController::~PlayerController()
{
}

SB::Vector2f PlayerController::Update(const float aDeltaTime)
{
	SB::Vector2f direction;
	if (myInputListener.GetIfKeyDown(SB::KeyboardKey::eRight) == true)
	{
		direction.x += 1.f;
	}

	if (myInputListener.GetIfKeyDown(SB::KeyboardKey::eLeft) == true)
	{
		direction.x -= 1.f;
	}

	if (myInputListener.GetIfKeyDown(SB::KeyboardKey::eDown) == true)
	{
		direction.y += 1.f;
	}

	if (myInputListener.GetIfKeyDown(SB::KeyboardKey::eUp) == true)
	{
		direction.y -= 1.f;
	}

	return direction.GetNormalized() * PlayerSpeed * aDeltaTime;
}
