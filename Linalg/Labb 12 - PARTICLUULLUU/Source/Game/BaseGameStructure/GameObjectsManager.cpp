#include "stdafx.h"
#include "GameObjectsManager.h"
#include <cassert>
#include "GameObjects\TemplateGameObject.h"
#include "../DX2DEngine/tga2d/engine.h"




GameObjectsManager *GameObjectsManager::ourInstance;

GameObjectsManager::GameObjectsManager()
{
	ourInstance = nullptr;
	myDrawQue.Init(100);
	myCamera = Camera(static_cast<float>(DX2D::CEngine::GetInstance()->GetWindowSize().y), static_cast<float>(DX2D::CEngine::GetInstance()->GetWindowSize().x), Vector3f(0.f, 0.f, 0.f));

	myBadSolution = new DX2D::CSpriteBatch(true);
	myBadSolution->Init("Sprites/chokladboll.dds");
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

void GameObjectsManager::SetCameraPosition(Vector3f aPosition)
{
	ourInstance->myCamera.SetPosition(aPosition);
}

//void GameObjectsManager::IncreaseCameraPosition(Vector3f aPosition)
//{
//	ourInstance->myCamera.IncreasePosition(aPosition);
//}

void GameObjectsManager::IncreaseCameraForward(float aDelta)
{
	ourInstance->myCamera.IncreaseForward(aDelta);
}

void GameObjectsManager::IncreaseCameraRight(float aDelta)
{
	ourInstance->myCamera.IncreaseRight(aDelta);
}

void GameObjectsManager::IncreaseCameraYaw(float aRadian)
{
	ourInstance->myCamera.IncreaseYaw(aRadian);
}

void GameObjectsManager::IncreaseCameraPitch(float aRadian)
{
	ourInstance->myCamera.IncreasePitch(aRadian);
}

void GameObjectsManager::IncreaseCameraRoll(float aRadian)
{
	ourInstance->myCamera.IncreaseRoll(aRadian);
}


void GameObjectsManager::AddRenderToQue(const RenderCommands & aRenderCommand)
{
	GetInstance()->myDrawQue.Add(aRenderCommand);
}

void GameObjectsManager::DrawAllCommands()
{
	//DX2D::CSprite * daPointer;
	//CU::GrowingArray<DX2D::CSprite*, LONGLONG> tempPointers;
	//tempPointers.Init(10000000);

	CU::GrowingArray<DX2D::CSpriteBatch*> batches;
	batches.Init(3);

	for (size_t iCommand = 0; iCommand < myDrawQue.Size(); ++iCommand)
	{
		const unsigned short tempIndex = batches.Find(myDrawQue[iCommand].GetBatch());

		if (tempIndex == batches.FoundNone)
		{
			batches.Add(myDrawQue[iCommand].GetBatch());
		}

		myDrawQue[iCommand].Render(myCamera);

	
	}

	//myBadSolution->Render();
	//myBadSolution->ClearAll();

	for (unsigned short iBatches = 0; iBatches < batches.Size(); ++iBatches)
	{
		batches[iBatches]->Render();
	}

	for (unsigned short iBatches = 0; iBatches < batches.Size(); ++iBatches)
	{
		batches[iBatches]->ClearAll();
	}

	//tempPointers.DeleteAll();

	batches.RemoveAll();
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