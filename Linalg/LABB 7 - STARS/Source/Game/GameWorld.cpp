#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include "../CommonUtilities/Macros.h"
#include <sstream>
#include "TinyXML2/tinyxml2.h"
#include <iostream>
#include "BaseGameStructure\GameObjectsManager.h"
#include "../CommonUtilities/Vectors/Vector.h"


const size_t StarAmount = 100000;

//using namespace DX2D;
CGameWorld::CGameWorld()
{
	testRotation = 0.f;

	myCameraSpeed = 10.f;

	myDistribution = std::uniform_real_distribution<float>(-10.f, 10.f);
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{
	myInput.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));

	float randomY = myDistribution(myRandomGenerator);
	float randomX = myDistribution(myRandomGenerator);
	float randomZ = myDistribution(myRandomGenerator);

	myStars.Init(Vector3f(randomX, randomY, randomZ), nullptr);

	float tempRandomNumber = myDistribution(myRandomGenerator);

	for (size_t iStar = 0; iStar < StarAmount; ++iStar)
	{
		randomY = myDistribution(myRandomGenerator);
		randomX = myDistribution(myRandomGenerator);
		randomZ = myDistribution(myRandomGenerator);

		myStars.AddChild(Vector3f(randomX, randomY, randomZ), nullptr);
	}
	

	GameObjectsManager::SetCameraPosition(Vector3f( 0.5f, 0.5f, 0.0f));
}

void CGameWorld::Update(float aTimeDelta)
{
	GameObjectsManager::Update(aTimeDelta);

	myInput.Update();

	if (myInput.GetKeyDown(DIK_W))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(myCameraSpeed * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_S))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(-myCameraSpeed * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_A))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(-myCameraSpeed * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_D))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(myCameraSpeed * aTimeDelta);
	}



	if (myInput.GetKeyDown(DIK_UPARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(-0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_DOWNARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_RIGHTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(0.5f * aTimeDelta);
	}

	if (myInput.GetKeyDown(DIK_LEFTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(-0.5f * aTimeDelta);
	}
}

void CGameWorld::Draw()
{
	GameObjectsManager::Draw();
}