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
	myRandomizer.SetSeed();
	myRandomizer.SetMinMax(-0.3f, 0.3f);

	CU::MainSingleton::Create();
	GET_INPUT.Initialize();

	myCamera.Init(500.f, 500.f, CU::Vector3f(0.f, 0.0f, -2.6f));

	myPrettyModel.Init("Models/companion.fbx");
	//myPrettyModel.SetPosition(CU::Vector3f(0.f, 0.f, 2.0f));
}

void CGame::Update()
{
	myPrettyModel.Rotate();
	const float deltaTime = GET_DELTA_SECONDS;
	
	CU::MainSingleton::GetTimerManager().Update();
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
		myCamera.IncreasePitch(-100.f * deltaTime);
	}
	else if (GET_INPUT.GetKeyDown(DIK_DOWNARROW) == true)
	{
		myCamera.IncreasePitch(100.f * deltaTime);
	}

	if (GET_INPUT.GetKeyDown(DIK_RIGHTARROW) == true)
	{
		myCamera.IncreaseYaw(100.f * deltaTime);
	}
	else if (GET_INPUT.GetKeyDown(DIK_LEFTARROW) == true)
	{
		myCamera.IncreaseYaw(-100.f * deltaTime);
	}

	myCamera.MovePosition(tempToAddCameraPosition);
}

void CGame::Render()
{
	//RenderCubeAtPosition(CU::Vector3f(0.f, 0.f, 0.5f), CU::Vector3f(0.2f, 0.2f, 0.2f));
	myPrettyModel.Render(myCamera);
}

void CGame::RenderCubeAtPosition(const CU::Vector3f & aPosition, const CU::Vector3f & aScale /*= CU::Vector3f::One*/)
{
	CHUGModel prettyCube;
	prettyCube.InitAsCube(aPosition, aScale);
	prettyCube.Render(myCamera);
}

