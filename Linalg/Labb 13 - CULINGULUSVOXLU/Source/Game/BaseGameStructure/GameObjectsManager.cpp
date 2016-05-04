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
	myCamera = Camera(DX2D::CEngine::GetInstance()->GetWindowSize().y, DX2D::CEngine::GetInstance()->GetWindowSize().x, Vector3f(0.f, 0.f, 0.f));
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


const Intersection3D::Fov90Frustum & GameObjectsManager::GetCameraFrustum()
{
	return ourInstance->myCamera.GetFrustum();
}

const Matrix44f & GameObjectsManager::GetCameraInverse()
{
	return GetInstance()->myCamera.GetInverse();
}

void GameObjectsManager::AddRenderToQue(const RenderCommands aRenderCommand)
{
	GetInstance()->myDrawQue.Add(aRenderCommand);
}

void GameObjectsManager::DrawAllCommands()
{
	for (size_t iCommand = 0; iCommand < myDrawQue.Size(); ++iCommand)
	{
		myDrawQue[iCommand].Render(myCamera);
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