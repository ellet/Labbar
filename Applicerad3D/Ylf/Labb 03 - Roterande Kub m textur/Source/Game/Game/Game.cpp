#include "stdafx.h"
#include "Game/Game.h"
#include <Engine/HUGEngine.h>
#include <CU/Systems/MainSingleton/MainSingleton.h>
#include <dinput.h>

CGame::CGame()
{
}

CGame::~CGame()
{
	CU::MainSingleton::Destroy();
}

void CGame::Init()
{
	CU::MainSingleton::Create();
	GET_INPUT.Initialize();

	myCamera.Init(500.f, 500.f, CU::Vector3f(0.f, 0.0f, -0.6f));
	//myQuad.InitAsQuad();
	myCube.InitAsCube();
}

void CGame::Update()
{
	myCube.Rotate();
	const float fakeDeltaTime = 0.00001f;

	GET_INPUT.Update();

	CU::Vector3f tempToAddCameraPosition = CU::Vector3f::Zero;

	if (GET_INPUT.GetKeyDown(DIK_W) == true)
	{
		tempToAddCameraPosition.y += 0.00005f;
	}
	else if (GET_INPUT.GetKeyDown(DIK_S) == true)
	{
		tempToAddCameraPosition.y -= 0.00005f;
	}

	if (GET_INPUT.GetKeyDown(DIK_D) == true)
	{
		tempToAddCameraPosition.x += 0.00005f;
	}
	else if (GET_INPUT.GetKeyDown(DIK_A) == true)
	{
		tempToAddCameraPosition.x -= 0.00005f;
	}

	if (GET_INPUT.GetKeyDown(DIK_Q) == true)
	{
		tempToAddCameraPosition.z += 0.00005f;
	}
	else if (GET_INPUT.GetKeyDown(DIK_E) == true)
	{
		tempToAddCameraPosition.z -= 0.00005f;
	}

	if (GET_INPUT.GetKeyDown(DIK_UPARROW) == true)
	{
		myCamera.IncreasePitch(-100.f  * fakeDeltaTime);
	}
	else if (GET_INPUT.GetKeyDown(DIK_DOWNARROW) == true)
	{
		myCamera.IncreasePitch(100.f * fakeDeltaTime);
	}

	if (GET_INPUT.GetKeyDown(DIK_RIGHTARROW) == true)
	{
		myCamera.IncreaseYaw(100.f * fakeDeltaTime);
	}
	else if (GET_INPUT.GetKeyDown(DIK_LEFTARROW) == true)
	{
		myCamera.IncreaseYaw(-100.f * fakeDeltaTime);
	}

	myCamera.MovePosition(tempToAddCameraPosition);
}

void CGame::Render()
{
	//myQuad.Render();
	myCube.Render(myCamera);
	//myTriangle.Render();
}
