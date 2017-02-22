#include "stdafx.h"
#include "Ball.h"
#include <cstdlib>
#include <tga2d/sprite/sprite.h>

const float BallStartSpeed = 0.5f;
const float BallSpeedIncrease = 0.1f;

CBall::CBall()
{
	mySprite = nullptr;
}

CBall::~CBall()
{
	delete mySprite;
	mySprite = nullptr;
}

void CBall::Init()
{
	mySprite = new DX2D::CSprite("sprites/ball.png");
}

void CBall::Reset()
{
	myPosition.x = 0.5f;
	myPosition.y = (rand() % 100) / 100.f;
	myVelocity.x = BallStartSpeed * (((rand() % 2) * 2) - 1);
	myVelocity.y = BallStartSpeed * (((rand() % 2) * 2) - 1);
}

void CBall::Update(const float aDeltaTime)
{
	myPosition += myVelocity * aDeltaTime;
	mySprite->SetPosition(myPosition);
	myVelocity *= 1 + (BallSpeedIncrease * aDeltaTime);

	if (myPosition.y <= 0 || myPosition.y >= 1 - mySprite->GetSize().y)
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
	mySprite->Render();
}

float CBall::GetWidth() const
{
	return mySprite->GetSize().x;
}

float CBall::GetHeight() const
{
	return mySprite->GetSize().y;
}