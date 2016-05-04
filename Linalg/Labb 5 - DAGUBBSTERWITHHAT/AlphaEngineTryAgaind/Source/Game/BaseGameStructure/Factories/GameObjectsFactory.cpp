#include "stdafx.h"
#include "GameObjectsFactory.h"
#include "../GameObjects/TemplateGameObject.h"


GameObjectsFactory::GameObjectsFactory()
{
	myGameObjects.Init(100, false);
}



GameObjectsFactory::~GameObjectsFactory()
{
}


BaseGameObject & GameObjectsFactory::GetBaseGameObject(size_t aIndex)
{
	return myGameObjects[aIndex];
}


void GameObjectsFactory::UpdateAllGameObjects(float aDeltaTime)
{
	for (size_t iGameObject = 0; iGameObject < myGameObjects.Size(); ++iGameObject)
	{
		myGameObjects[iGameObject].Update(aDeltaTime);
	}
}


void GameObjectsFactory::DrawAllGameObjects()
{
	for (size_t iGameObject = 0; iGameObject < myGameObjects.Size(); ++iGameObject)
	{
		myGameObjects[iGameObject].Draw();
	}
}











//#pragma region CreateObjects
//
//TemplateGameObject GameObjectsFactory::CreateTemplateObject()
//{
//	TemplateGameObject derp;
//	derp.Init(GetNewBaseGameObjectIndex());
//	return derp;
//}
//
//
//#pragma endregion

size_t GameObjectsFactory::GetNewBaseGameObjectIndex()
{
	myGameObjects.Add(BaseGameObject());

	return myGameObjects.Size()-1;
}