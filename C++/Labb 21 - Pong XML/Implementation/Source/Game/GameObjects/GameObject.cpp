#include "stdafx.h"
#include "GameObject.h"

#include <math.h>
#include <cmath>

#include <tga2d/Engine.h>
#include <tga2d/math/vector2.h>

#include <Macros.h>

GameObject::GameObject()
{
	myObject = nullptr;
}


GameObject::~GameObject()
{
	SAFE_DELETE(myObject);
}

void GameObject::Init(const char* aTexturePath)
{
	myObject = new DX2D::CSprite(aTexturePath);
	myObject->SetPosition(DX2D::Vector2f(0.f, 0.f));
	
	myHeight = myObject->GetSize().y;
	myWidth = myObject->GetSize().x;

	SetCollisionBox();

	mySpeed = 0;
	myXSpeed = 0;
	myYSpeed = 0;
	myDirection = 0;

	myMaxSpeed = 0.75f;
	myFriction = 0.25f;

	myIUseFriction = true;
	myICanGoOutside = false;
}

void GameObject::Draw()
{
	myObject->Render();
}

void GameObject::Update(float aDeltaTime)
{
	if (mySpeed > 0)
	{
		DX2D::Vector2f position = myObject->GetPosition();
		position.x += myXSpeed * aDeltaTime;
		position.y += -myYSpeed * aDeltaTime;


		mySpeed = CLAMP(mySpeed, 0.0f, myMaxSpeed);
		SetPosition(position.x, position.y);

		SetCollisionBox();

		if (myIUseFriction == true)
		{
			const float TempFriction = myFriction * aDeltaTime;
			if (mySpeed > mySpeed - TempFriction)
			{
				mySpeed = mySpeed - TempFriction;
			}
			else
			{
				mySpeed = 0;
			}
		}
	}
}

void GameObject::Bounce()
{
	myYSpeed = -myYSpeed;
	SetDirectionFromAngleSpeeds();
	myObject->SetPosition(myPreviousPosition);
}

void GameObject::CheckCollision(const CollisionRectangle & aRectangle)
{
	/*if ((myCollisionRectangle.myTopLeft.x >= aRectangle.myTopLeft.x 
		&& myCollisionRectangle.myTopLeft.x <= aRectangle.myBottomRight.x)
		&& (myCollisionRectangle.myTopLeft.y >= aRectangle.myTopLeft.y 
		&& myCollisionRectangle.myTopLeft.y <= aRectangle.myBottomRight.y))*/
	if (myCollisionRectangle.myTopLeft.x > aRectangle.myBottomRight.x)
	{
		return;
	}

	if (myCollisionRectangle.myBottomRight.x < aRectangle.myTopLeft.x)
	{
		return;
	}

	if (myCollisionRectangle.myBottomRight.y < aRectangle.myTopLeft.y)
	{
		return;
	}

	if (myCollisionRectangle.myTopLeft.y > aRectangle.myBottomRight.y)
	{
		return;
	}

	{
		DoCollision();
	}
}

void GameObject::DoCollision()
{
	myXSpeed = -myXSpeed;
	SetDirectionFromAngleSpeeds();
	myObject->SetPosition(myPreviousPosition);
}

void GameObject::SetPosition(float aXPosition, float aYPosition)
{
	if (myICanGoOutside == false)
	{
		aXPosition = CLAMP(1.0f -myWidth, 0.0f, aXPosition);
		aYPosition = CLAMP(1.0f -myHeight, 0.0f, aYPosition);
	}
	else
	{
		if (aYPosition > (1.f - myHeight) || aYPosition < 0.f)
		{
			Bounce();
		}
	}

	myPreviousPosition = myObject->GetPosition();
	myObject->SetPosition(DX2D::Vector2f(aXPosition, aYPosition));
}

void GameObject::SetMovement(float aDirection, float aSpeed, bool aTrueSet)
{
	if (aDirection != myDirection)
	{
		if ((mySpeed - aSpeed) > 0)
		{
			aDirection = myDirection;
			aSpeed = -aSpeed;
		}
	}

	if (aTrueSet == true)
	{
		mySpeed = aSpeed;
	}
	else
	{
		mySpeed += aSpeed;
	}

	myDirection = aDirection;
	myXSpeed = GetXSpeed();
	myYSpeed = GetYSpeed();

	mySpeed = CLAMP(mySpeed, 0.0f, myMaxSpeed);
}



void GameObject::SetDirectionFromAngleSpeeds()
{
	const float TempDegressInRadians = std::sinhf(myYSpeed / myXSpeed);
	myDirection = RADIANS_TO_DEGRESSF(TempDegressInRadians);
	AddDirection(0);
}


float GameObject::GetXSpeed()
{
	return std::cos(DEGRESS_TO_RADIANSF(myDirection)) * mySpeed;
}

float GameObject::GetYSpeed()
{
	return std::sin(DEGRESS_TO_RADIANSF(myDirection)) * mySpeed;
}