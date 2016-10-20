#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::PhysicsUpdate(const float aDeltaTime)
{
	myMoveToPosition += myVelocity * aDeltaTime;
}

void Entity::ApplyPosition()
{
	myPosition = myMoveToPosition;
}

void Entity::SetPosition(const CommonUtilities::Vector2f & aPosition)
{
	myPosition = aPosition;
	myMoveToPosition = aPosition;
}

void Entity::SetMoveToPosition(const CommonUtilities::Vector2f & aPosition)
{
	myMoveToPosition = aPosition;
}

void Entity::SetSize(const CommonUtilities::Vector2f & aSize)
{
	mySize = aSize;
}

void Entity::SetVelocity(const CommonUtilities::Vector2f & aVelocity)
{
	myVelocity = aVelocity;
}

