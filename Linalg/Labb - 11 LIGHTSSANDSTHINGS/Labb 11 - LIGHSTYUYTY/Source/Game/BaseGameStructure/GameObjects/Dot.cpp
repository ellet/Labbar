#include "stdafx.h"
#include "Dot.h"
#include "../GameObjectsManager.h"


DotGameObject::DotGameObject()
{
	
}


DotGameObject::~DotGameObject()
{
}


void DotGameObject::Init(Vector3<float> aPosition, const WorldSpace * aWorldSpace, const char * aFilePath)
{
	myBaseGameObjectIndex = GameObjectsManager::GetNewBaseGameObjectIndex();
	GetMyBaseGameObject().Init(aFilePath, aWorldSpace, aPosition);
}

BaseGameObject & DotGameObject::GetMyBaseGameObject()
{
	return GameObjectsManager::GetBaseGameObject(myBaseGameObjectIndex);
}

Vector3<float> DotGameObject::GetPosition()
{
	return GetMyBaseGameObject().GetPosition();
}

void DotGameObject::SetPosition(Vector3<float> aPosition)
{
	GetMyBaseGameObject().SetPosition(aPosition);
}