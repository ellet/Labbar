#include "stdafx.h"
#include "GameObjectsManager.h"
#include <cassert>
#include "GameObjects\TemplateGameObject.h"

GameObjectsManager *GameObjectsManager::ourInstance;

GameObjectsManager::GameObjectsManager()
{
	ourInstance == nullptr;
	myDrawQue.Init(100);
}


GameObjectsManager::~GameObjectsManager()
{
}

void GameObjectsManager::CreateGameObjectsManager()
{
	assert(ourInstance == nullptr && "GameObjects manager allready created");

	ourInstance = new GameObjectsManager;
}

BaseGameObject & GameObjectsManager::GetBaseGameObject(size_t aIndex)
{
	return GetInstance()->myFactory.GetBaseGameObject(aIndex);
}

void GameObjectsManager::Update(float aDeltaTime)
{
	GetInstance()->myFactory.UpdateAllGameObjects(aDeltaTime);
}

void GameObjectsManager::Draw()
{
	GetInstance()->myFactory.DrawAllGameObjects();

	GetInstance()->DrawAllCommands();
}

GameObjectsManager* GameObjectsManager::GetInstance()
{
	assert(ourInstance != nullptr && "GameObjects manager is nullptr");

	return ourInstance;
}

size_t GameObjectsManager::GetNewBaseGameObjectIndex()
{
	return GetInstance()->myFactory.GetNewBaseGameObjectIndex();
}

void GameObjectsManager::AddRenderToQue(const RenderCommands aRenderCommand)
{
	GetInstance()->myDrawQue.Add(aRenderCommand);
}

void GameObjectsManager::DrawAllCommands()
{
	for (size_t iCommand = 0; iCommand < myDrawQue.Size(); ++iCommand)
	{
		myDrawQue[iCommand].Render();
	}

	myDrawQue.RemoveAll();
}

//#pragma region CreateObjects
//
//TemplateGameObject GameObjectsManager::GetNewTemplateGameObject()
//{
//	return GetInstance()->myFactory.CreateTemplateObject();
//}
//
//
//#pragma endregion