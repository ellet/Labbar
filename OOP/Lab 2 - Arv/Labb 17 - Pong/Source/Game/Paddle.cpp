#include "stdafx.h"
#include "Paddle.h"
#include "ball.h"
#include <tga2d/sprite/sprite.h>
#include <InputWrapper\InputWrapper.h>

const float PaddleSpeed = 1.f;

Paddle::Paddle()
{
	mySprite = nullptr;
	myIsAI = false;
}

Paddle::~Paddle()
{
	delete mySprite;
	mySprite = nullptr;
}

void Paddle::Init(bool aMakeAI, Ball& aBall)
{
	myIsAI = aMakeAI;
	BaseInit("sprites/paddle.png", PaddleSpeed);
	myBallPointer = &aBall;
}

bool Paddle::Collides(const Ball& aBall)
{
	if (myPosition.x > aBall.GetPosition().x + aBall.GetWidth() ||
		myPosition.x + mySprite->GetSize().x < aBall.GetPosition().x ||
		myPosition.y > aBall.GetPosition().y + aBall.GetHeight() ||
		myPosition.y + mySprite->GetSize().y < aBall.GetPosition().y)
	{
		return false;
	}
	return true;
}

void Paddle::Update(const float aDeltaTime)
{
	Ball & aBall = *myBallPointer;

	if (myIsAI == true)
	{
		if (aBall.GetPosition().y + aBall.GetHeight() / 2 > myPosition.y + mySprite->GetSize().y / 2)
		{
			MoveDown(aDeltaTime);
		}
		else
		{
			MoveUp(aDeltaTime);
		}
	}
	else
	{
		if (CommonUtilities::InputWrapper::GetKeyDown(DIK_UPARROW) == true)
		{
			MoveUp(aDeltaTime);
		}
		else if (CommonUtilities::InputWrapper::GetKeyDown(DIK_DOWNARROW) == true)
		{
			MoveDown(aDeltaTime);
		}
	}

	BaseUpdate(aDeltaTime);
}