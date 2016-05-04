#include "stdafx.h"
#include "Ball.h"
#include <cstdlib>
#include <tga2d/sprite/sprite.h>

const float BallStartSpeed = 0.5f;
const float BallAcceleration = 0.1f;

Ball::Ball()
{
	mySprite = nullptr;
	myBallStartSpeed = BallStartSpeed;
	myBallAcceleration = BallAcceleration;
}

Ball::~Ball()
{
	delete mySprite;
	mySprite = nullptr;
}

void Ball::Init(const picojson::value::object &aJSONObject)
{
	std::string gfx = aJSONObject.at("gfx").get<std::string>();
	mySprite = new DX2D::CSprite(gfx.c_str());

	myBallStartSpeed = static_cast<float>(aJSONObject.at("startspeed").get<double>());
	myBallAcceleration = static_cast<float>(aJSONObject.at("acc").get<double>());
}

void Ball::Reset()
{
	myPosition.x = 0.5f;
	myPosition.y = (rand() % 100) / 100.f;
	myVelocity.x = myBallStartSpeed * (((rand() % 2) * 2) - 1);
	myVelocity.y = myBallStartSpeed * (((rand() % 2) * 2) - 1);
}

void Ball::Update(const float aDeltaTime)
{
	myPosition += myVelocity * aDeltaTime;
	mySprite->SetPosition(myPosition);
	myVelocity *= 1 + (myBallAcceleration * aDeltaTime);

	if (myPosition.y <= 0 || myPosition.y >= 1 - mySprite->GetSize().y)
	{
		myVelocity.y *= -1;
	}
}

void Ball::ReverseDirection()
{
	myVelocity.x *= -1;
}

void Ball::Draw()
{
	mySprite->Render();
}

float Ball::GetWidth() const
{
	return mySprite->GetSize().x;
}

float Ball::GetHeight() const
{
	return mySprite->GetSize().y;
}