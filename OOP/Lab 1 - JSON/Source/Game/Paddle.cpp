#include "stdafx.h"
#include "Paddle.h"
#include "ball.h"
#include "../tinyxml2/tinyxml2.h"
#include <tga2d/sprite/sprite.h>
#include "..\CommonUtilites\InputWrapper.h"


const float PaddleSpeed = 1.f;

Paddle::Paddle()
{
	mySprite = nullptr;
	myIsAI = false;
	myPaddleSpeed = PaddleSpeed;
}

Paddle::~Paddle()
{
	delete mySprite;
	mySprite = nullptr;
}

void Paddle::Init(picojson::object & aPicoObject, bool aMakeAI)
{
	myIsAI = aMakeAI;
	mySprite = new DX2D::CSprite(aPicoObject.find("sprite")->second.get<std::string>().c_str());
	myPaddleSpeed = static_cast<float>(aPicoObject.find("speed")->second.get<double>());
}

void Paddle::SetPosition(const float aX, const float aY)
{
	myPosition.Set(aX, aY);
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

void Paddle::Draw()
{
	mySprite->Render();
}

void Paddle::Update(const float aDeltaTime, const Input::InputWrapper& aInputWrapper, const Ball& aBall)
{
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
		if (aInputWrapper.GetKeyDown(DIK_UPARROW) == true)
		{
			MoveUp(aDeltaTime);
		}
		else if (aInputWrapper.GetKeyDown(DIK_DOWNARROW) == true)
		{
			MoveDown(aDeltaTime);
		}
	}

	mySprite->SetPosition(myPosition);
}

void Paddle::MoveUp(const float aDeltaTime)
{
	if (myPosition.y - aDeltaTime * PaddleSpeed > 0)
	{
		myPosition.y -= aDeltaTime * PaddleSpeed;
	}
}

void Paddle::MoveDown(const float aDeltaTime)
{
	if (myPosition.y + aDeltaTime * PaddleSpeed < 1 - mySprite->GetSize().y)
	{
		myPosition.y += aDeltaTime * PaddleSpeed;
	}
}
