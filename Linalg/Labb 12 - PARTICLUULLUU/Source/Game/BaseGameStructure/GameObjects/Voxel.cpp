#include "stdafx.h"
#include "Voxel.h"
#include "../GameObjectsManager.h"

Voxel::Voxel()
{
}


Voxel::~Voxel()
{
}

void Voxel::Init(Vector3<float> aPosition, float aSize, const WorldSpace * aWorldSpace, const char * aFilePath)
{
	myBaseGameObjectIndex = GameObjectsManager::GetNewBaseGameObjectIndex();
	Vector4f colour(((aPosition + Vector3f::One)));
	GetMyBaseGameObject().Init(aFilePath, aWorldSpace, (aPosition * aSize), colour);

}

BaseGameObject & Voxel::GetMyBaseGameObject()
{
	return GameObjectsManager::GetBaseGameObject(myBaseGameObjectIndex);
}