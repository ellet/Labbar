#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include <Macros/Macros.h>
#include <sstream>
#include "TinyXML2/tinyxml2.h"
#include <iostream>
#include "BaseGameStructure\GameObjectsManager.h"
#include "../CommonUtilities/Vectors/Vector.h"
#include "CreatePlane.h"

#include <tga2d/sprite/sprite.h>
#include <Particles/Manager/ParticleSystemManager.h>
//#include "BaseGameStructure/GameObjectsManager.h"

const size_t StarAmount = 100000;

//using namespace DX2D;
CGameWorld::CGameWorld()
{
	testRotation = 0.f;

	myCameraSpeed = 4.f;

	myDistribution = std::uniform_real_distribution<float>(0.f, 1.f);
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{
	GameObjectsManager::SetCameraPosition(Vector3f( 0.f, 0.f, -1.0));
}

void CGameWorld::Update(float aTimeDelta)
{
	CU::InputWrapper::Update();
	GameObjectsManager::Update(aTimeDelta);
	ParticleSystemManager::Update(aTimeDelta);
	

	if (CU::InputWrapper::GetKeyDown(DIK_W))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(myCameraSpeed * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_S))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitZ * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraForward(-myCameraSpeed * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_A))
	{
		//GameObjectsManager::IncreaseCameraPosition(-Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(-myCameraSpeed * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_D))
	{
		//GameObjectsManager::IncreaseCameraPosition(Vector3f::UnitX * myCameraSpeed * aTimeDelta);
		GameObjectsManager::IncreaseCameraRight(myCameraSpeed * aTimeDelta);
	}



	if (CU::InputWrapper::GetKeyDown(DIK_UPARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(-0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_DOWNARROW))
	{
		GameObjectsManager::IncreaseCameraPitch(0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_RIGHTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(0.5f * aTimeDelta);
	}

	if (CU::InputWrapper::GetKeyDown(DIK_LEFTARROW))
	{
		GameObjectsManager::IncreaseCameraYaw(-0.5f * aTimeDelta);
	}

}

void CGameWorld::Draw()
{
	GameObjectsManager::Draw();
	ParticleSystemManager::Draw();
}