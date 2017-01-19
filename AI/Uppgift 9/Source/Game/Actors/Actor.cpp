#include "stdafx.h"
#include "Actor.h"
#include "Controllers\BaseController.h"


Actor::Actor()
{
	myController = nullptr;
}


Actor::~Actor()
{
}

void Actor::Update(const float aDeltaTime)
{
	if (myController != nullptr)
	{
		const SB::Vector2f moveDelta = myController->Update(aDeltaTime);

		AddToPosition(moveDelta);
	}
}

void Actor::Render() const
{
	mySprite.Render();
}

void Actor::SetSprite(const std::string & aFilePath)
{
	mySprite.Init(aFilePath);
}

const SB::Vector2f & Actor::GetPosition() const
{
	return myPosition;
}

void Actor::SetPosition(const SB::Vector2f aPosition)
{
	myPosition = aPosition;
	mySprite.SetPosition(myPosition);
}

void Actor::AddToPosition(const SB::Vector2f & aDelta)
{
	SetPosition(GetPosition() + aDelta);
}
