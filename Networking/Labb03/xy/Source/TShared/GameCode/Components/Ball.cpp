#include "stdafx.h"
#include "Ball.h"
#include <cstdlib>
#include <tga2d/sprite/sprite.h>
#include <GameCode/GameObject/GameObject.h>
#include <tga2d/math/vector2.h>
#include "RenderComponent.h"

const float BallStartSpeed = 0.5f;
const float BallSpeedIncrease = 0.1f;

CBall::CBall()
{
}

CBall::~CBall()
{
}

void CBall::Init()
{
	mySize = { 0.0125000002f, 0.0222222228f };
}

void CBall::Reset()
{
	myOwner->myPosition.x = 0.5f;
	myOwner->myPosition.y = (rand() % 100) / 100.f;
	myVelocity.x = BallStartSpeed * (((rand() % 2) * 2) - 1);
	myVelocity.y = BallStartSpeed * (((rand() % 2) * 2) - 1);
}

const DX2D::Vector2f& CBall::GetPosition() const
{
	return myOwner->myPosition;
}

void CBall::Update(const float aDeltaTime)
{
	myOwner->myPosition += myVelocity * aDeltaTime;
	myVelocity *= 1 + (BallSpeedIncrease * aDeltaTime);

	if (myOwner->myPosition.y <= 0 || myOwner->myPosition.y >= 1 - mySize.y)
	{
		myVelocity.y *= -1;
	}
}

void CBall::ReverseDirection()
{
	myVelocity.x *= -1;
}

void CBall::Render()
{
}

float CBall::GetWidth() const
{
	return mySize.x;
}

float CBall::GetHeight() const
{
	return mySize.y;
}
