#include "stdafx.h"
#include "Dot.h"
#include "../GameObjectsManager.h"
#include "../Game/BaseGameStructure/Rendering/WorldSpace.h"


DotGameObject::DotGameObject()
{
	
}


DotGameObject::~DotGameObject()
{
}


void DotGameObject::Init(Vector2<float> aPosition, WorldSpace * aWorldSpace)
{
	myBaseGameObjectIndex = GameObjectsManager::GetNewBaseGameObjectIndex();
	
	GetMyBaseGameObject().Init("sprites/DotFORGUBBEWITHHAT.png", aWorldSpace, aPosition);
}

BaseGameObject & DotGameObject::GetMyBaseGameObject()
{
	return GameObjectsManager::GetBaseGameObject(myBaseGameObjectIndex);
}

Vector2<float> DotGameObject::GetPosition()
{
	return GetMyBaseGameObject().GetPosition();
}

void DotGameObject::SetPosition(Vector2<float> aPosition)
{
	GetMyBaseGameObject().SetPosition(aPosition);
}