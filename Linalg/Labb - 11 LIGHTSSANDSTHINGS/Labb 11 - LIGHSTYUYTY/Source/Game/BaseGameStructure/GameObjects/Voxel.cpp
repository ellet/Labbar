#include "stdafx.h"
#include "Voxel.h"
#include "../GameObjectsManager.h"
#include "../../StuffsForLabs/VoxelData.h"

Voxel::Voxel()
{
}


Voxel::~Voxel()
{
}

void Voxel::Init(Vector3<float> aPosition, Vector3<float> aColour,
	Vector3<float> aNormal, float aSize, const WorldSpace * aWorldSpace, const char * aFilePath)
{
	myBaseGameObjectIndex = GameObjectsManager::GetNewBaseGameObjectIndex();
	Vector4f colour(((aColour)));
	GetMyBaseGameObject().Init(aFilePath, aWorldSpace, (aPosition * aSize), colour, aNormal);

}

void Voxel::Init(const VoxelData & aVoxel, 
	float aSize,
	const WorldSpace * aWorldSpace,
	const char * aFilePath)
{
	Init(aVoxel.myPosition, aVoxel.myColour, aVoxel.myNormal, aSize, aWorldSpace, aFilePath);
}

BaseGameObject & Voxel::GetMyBaseGameObject()
{
	return GameObjectsManager::GetBaseGameObject(myBaseGameObjectIndex);
}