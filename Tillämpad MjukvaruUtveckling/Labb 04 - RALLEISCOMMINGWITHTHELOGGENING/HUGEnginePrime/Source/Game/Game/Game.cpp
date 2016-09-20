#include "stdafx.h"
#include "Game/Game.h"
#include <Engine/HUGEngine.h>
#include <dinput.h>

CGame::CGame()
{
}


CGame::~CGame()
{
}

void CGame::Init()
{
	//myCube.InitAsModel("Modeller/Asteroid/AsteroidPillarLarge3.fbx");
	myCube.InitAsCube();
	
	//myController.SetPosition({ 0.f, 0.0f, -1.5f });
}

void CGame::Update()
{
	GET_INPUT.Update();
	CU::TimeManager::Update();


	const float DeltaTime = CU::TimeManager::GetDeltaTime().GetSeconds();

	float cameraSpeed = 10.5f;
	float cameraTurnSpeed = 0.5f;

	myCube.Update(CU::TimeManager::GetDeltaTime());

	if (GET_INPUT.GetKeyDown(DIK_1) == true)
	{
		myCube.InitAsModel("Modeller/Asteroid/AsteroidPillarLarge1.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_2) == true)
	{
		myCube.InitAsModel("Modeller/Asteroid/AsteroidPillarLarge2.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_3) == true)
	{
		myCube.InitAsModel("Modeller/Asteroid/AsteroidPillarLarge3.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_4) == true)
	{
		myCube.InitAsModel("Modeller/crystalAsteroid/crystalAsteroidHigh.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_5) == true)
	{
		myCube.InitAsModel("Modeller/crystalAsteroid/crystalAsteroidMid.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_6) == true)
	{
		myCube.InitAsModel("Modeller/crystalAsteroid/crystalAsteroidLow.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_7) == true)
	{
		myCube.InitAsModel("Modeller/pillar/pillarShortObelisk.fbx");
	}
	if (GET_INPUT.GetKeyDown(DIK_8) == true)
	{
		myCube.InitAsModel("Modeller/tga_companioncube/companion.fbx");
	}

	if (GET_INPUT.GetKeyDown(DIK_D) == true)
	{
		myController.IncreaseRight(DeltaTime  * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_A) == true)
	{
		myController.IncreaseRight(-DeltaTime  * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_W) == true)
	{
		myController.IncreaseForward(DeltaTime  * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_S) == true)
	{
		myController.IncreaseForward(-DeltaTime  * cameraSpeed);
	}

	if (GET_INPUT.GetKeyDown(DIK_RIGHTARROW) == true)
	{
		myController.IncreaseYaw(DeltaTime  * cameraTurnSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_LEFTARROW) == true)
	{
		myController.IncreaseYaw(-DeltaTime  * cameraTurnSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_UPARROW) == true)
	{
		myController.IncreasePitch(-DeltaTime  * cameraTurnSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_DOWNARROW) == true)
	{
		myController.IncreasePitch(DeltaTime  * cameraTurnSpeed);
	}

	if (GET_INPUT.GetKeyDown(DIK_E) == true)
	{
		myController.IncreaseRoll(DeltaTime  * cameraTurnSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_Q) == true)
	{
		myController.IncreaseRoll(-DeltaTime  * cameraTurnSpeed);
	}

}

void CGame::Render()
{
	myCube.Render();
	//myTriangle.Render();
}
