#include "stdafx.h"
#include "GameObject.h"

#include <tga2d/sprite/sprite.h>
#include <InputWrapper\InputWrapper.h>

GameObject::GameObject()
{
	mySprite = nullptr;
}

GameObject::~GameObject()
{
	delete mySprite;
	mySprite = nullptr;
}

void GameObject::BaseInit(const char * aSpritePath, const float aBaseSpeed)
{
	mySprite = new DX2D::CSprite(aSpritePath);
	mySpeed = aBaseSpeed;
}

void GameObject::Draw()
{
	mySprite->Render();
}

void GameObject::BaseUpdate(const float aDeltaTime)
{
	mySprite->SetPosition(myPosition);
}

void GameObject::MoveUp(const float aDeltaTime)
{
	if (myPosition.y - aDeltaTime * mySpeed > 0)
	{
		myPosition.y -= aDeltaTime * mySpeed;
	}
}

void GameObject::MoveDown(const float aDeltaTime)
{
	if (myPosition.y + aDeltaTime * mySpeed < 1 - mySprite->GetSize().y)
	{
		myPosition.y += aDeltaTime * mySpeed;
	}
}
