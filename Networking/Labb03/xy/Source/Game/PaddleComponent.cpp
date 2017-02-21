#include "stdafx.h"
#include "PaddleComponent.h"
#include "ball.h"
#include <tga2d/sprite/sprite.h>
#include "..\CommonUtilites\InputWrapper.h"
#include "ComponentIds.h"
#include "GameObject.h"

const float PaddleSpeed = 1.f;
unsigned int CPaddleComponent::myID = EComponentIds::EComponentIds_CPaddleComponent;

CPaddleComponent::CPaddleComponent()
{
	mySprite = nullptr;
	myIsAI = false;
}

CPaddleComponent::~CPaddleComponent()
{
	delete mySprite;
	mySprite = nullptr;
}

void CPaddleComponent::Init(/*bool aMakeAI*/)
{
	/*myIsAI = aMakeAI;*/
	mySprite = new DX2D::CSprite("sprites/paddle.png");
}

void CPaddleComponent::SetPosition(const float aX, const float aY)
{
	myOwner->myPosition.Set(aX, aY);
}



void CPaddleComponent::OnMessage(CComponentMessageBase* aMessage)
{
	if (aMessage->IsType<CComponentMessageOnInput>())
	{
		CComponentMessageOnInput* message = static_cast<CComponentMessageOnInput*>(aMessage);
		myVelocity.Set(0, message->myMovement == CComponentMessageOnInput::MOVE_UP ? 1.0f : -1.0f);
	}
}

bool CPaddleComponent::Collides(const CBall& aBall)
{
	if (myOwner->myPosition.x > aBall.GetPosition().x + aBall.GetWidth() ||
		myOwner->myPosition.x + mySprite->GetSize().x < aBall.GetPosition().x ||
		myOwner->myPosition.y > aBall.GetPosition().y + aBall.GetHeight() ||
		myOwner->myPosition.y + mySprite->GetSize().y < aBall.GetPosition().y)
	{
		return false;
	}
	return true;
}

void CPaddleComponent::Render()
{

	mySprite->SetPosition(myOwner->myPosition);
	mySprite->Render();
}

void CPaddleComponent::Update(float aDeltaTime)
{
	if (myVelocity.y > 0)
	{
		MoveUp(aDeltaTime);
	}
	else if (myVelocity.y < 0)
	{
		MoveDown(aDeltaTime);
	}

	myVelocity.Set(0, 0);
}

void CPaddleComponent::MoveUp(const float aDeltaTime)
{
	if (myOwner->myPosition.y - aDeltaTime * PaddleSpeed > 0)
	{
		myOwner->myPosition.y -= aDeltaTime * PaddleSpeed;
	}
}

void CPaddleComponent::MoveDown(const float aDeltaTime)
{
	if (myOwner->myPosition.y + aDeltaTime * PaddleSpeed < 1 - mySprite->GetSize().y)
	{
		myOwner->myPosition.y += aDeltaTime * PaddleSpeed;
	}
}
