#include "stdafx.h"
#include "Ball.h"
#include <cstdlib>
#include <tga2d/sprite/sprite.h>

const float BallStartSpeed = 0.5f;
const float BallSpeedIncrease = 0.1f;

Ball::Ball()
{
	mySprite = nullptr;
}

Ball::~Ball()
{
	delete mySprite;
	mySprite = nullptr;
}

void Ball::Init()
{
	BaseInit("sprites/ball.png", BallStartSpeed);
}

void Ball::Reset()
{
	myPosition.x = 0.5f;
	myPosition.y = (rand() % 100) / 100.f;
	myVelocity.x = BallStartSpeed * (((rand() % 2) * 2) - 1);
	myVelocity.y = BallStartSpeed * (((rand() % 2) * 2) - 1);
}

void Ball::Update(const float aDeltaTime)
{
	myPosition += myVelocity * aDeltaTime;
	BaseUpdate(aDeltaTime);
	myVelocity *= 1 + (BallSpeedIncrease * aDeltaTime);

	if (myPosition.y <= 0 || myPosition.y >= 1 - mySprite->GetSize().y)
	{
		myVelocity.y *= -1;
	}
}

void Ball::ReverseDirection()
{
	myVelocity.x *= -1;
}

float Ball::GetWidth() const
{
	return mySprite->GetSize().x;
}

float Ball::GetHeight() const
{
	return mySprite->GetSize().y;
}