#pragma once
#include "../GameObjects/BaseGameObject.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"

class TemplateGameObject;

class GameObjectsFactory
{
public:
	GameObjectsFactory();
	~GameObjectsFactory();

	BaseGameObject & GetBaseGameObject(size_t aIndex);

	void UpdateAllGameObjects(float aDeltaTime);
	void DrawAllGameObjects();

	size_t GetNewBaseGameObjectIndex();
	/*void CollisionCheckAllGameObjects(float aDeltaTime);*/

//#pragma region CreateObjects
//
//	TemplateGameObject CreateTemplateObject();
//
//
//#pragma endregion

private:
	

	CommonUtilities::GrowingArray<BaseGameObject, unsigned int> myGameObjects;
};