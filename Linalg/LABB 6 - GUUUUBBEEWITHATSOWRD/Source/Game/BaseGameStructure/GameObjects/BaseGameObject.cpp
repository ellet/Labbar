#include "stdafx.h"
#include "BaseGameObject.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d\math\vector2.h>
#include "../Rendering/RenderCommands.h"
#include "../GameObjectsManager.h"


BaseGameObject::BaseGameObject()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;;
}


BaseGameObject::~BaseGameObject()
{
}

void BaseGameObject::Init(const char* aFilePath, const WorldSpace * aWorldSpace, Vector2<float> aPosition, Vector2<float> aSpeed)
{
	mySprite = new DX2D::CSprite(aFilePath);

	myLocalSpace = aWorldSpace;
	mySpeed = aSpeed;
	myPosition = aPosition;
}

void BaseGameObject::Update(float aDeltaTime)
{
	if (mySpeed.x > 0 || mySpeed.y > 0)
	{
		PerformMovement(aDeltaTime);
	}
}

void BaseGameObject::PerformMovement(float aDeltaTime)
{
	myPosition += (mySpeed * aDeltaTime);
}

void BaseGameObject::Draw()
{
	RenderCommands myRender;
	myRender.Init(mySprite, myPosition, myLocalSpace);

	GameObjectsManager::AddRenderToQue(myRender);
}

Vector2<float> BaseGameObject::GetPosition()
{
	return myPosition;
}

void BaseGameObject::SetPosition(Vector2<float> aPosition)
{
	myPosition = aPosition;
}