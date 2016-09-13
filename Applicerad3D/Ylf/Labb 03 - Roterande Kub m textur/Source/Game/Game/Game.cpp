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

	CU::MainSingleton::Create();
	GET_INPUT.Initialize();

	myCamera.Init(500.f, 500.f, CU::Vector3f(0.f, 0.0f, -0.6f));
	//myQuad.InitAsQuad();
	myCube.InitAsCube(CU::Vector3f::Zero, CU::Vector3f(0.3f, 0.3f, 0.3f));
	InitPileOfCubes();
}

void CGame::Update()
{
	//myCube.Rotate();
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
	//myCube.Render(myCamera);
	//myTriangle.Render();
	//RenderAllTheCubes();
	//RenderOneCubeALot();
	RenderPileOfCubes();
}

void CGame::RenderCubeAtPosition(const CU::Vector3f & aPosition, const CU::Vector3f & aScale /*= CU::Vector3f::One*/)
{
	CHUGModel prettyCube;
	prettyCube.InitAsCube(aPosition, aScale);
	prettyCube.Render(myCamera);
}

void CGame::RenderOneCubeALot()
{
	unsigned int cubeAmount = 1000;
	CU::Vector3f positionOffset = CU::Vector3f::Zero;

	for (unsigned int i = 0; i < cubeAmount; ++i)
	{
		//positionOffset = CU::Vector3f(myRandomizer.GetRandomValue(-0.5f, 0.5f), myRandomizer.GetRandomValue(-0.4f, 0.4f), myRandomizer.GetRandomValue(-0.2f, 0.2f));

		myCube.SetPosition(positionOffset);
		myCube.Render(myCamera);
	}
}

void CGame::RenderAllTheCubes()
{
	unsigned int cubeAmount = 100;
	CU::Vector3f positionOffset = CU::Vector3f::Zero;

	for (unsigned int i = 0; i < cubeAmount; ++i)
	{
		//positionOffset = CU::Vector3f(myRandomizer.GetRandomValue(-0.5f, 0.5f), myRandomizer.GetRandomValue(-0.4f, 0.4f), myRandomizer.GetRandomValue(-0.2f, 0.2f));

		RenderCubeAtPosition(CU::Vector3f(
			0.f + positionOffset.x,
			0.f + positionOffset.y,
			0.f + positionOffset.z),
			CU::Vector3f(0.6f, 0.6f, 0.6f));
	}
}

void CGame::RenderPileOfCubes()
{
	for (unsigned int i = 0; i < myPileOfCubes.Size(); ++i)
	{
		myPileOfCubes[i].Render(myCamera);
	}
}

void CGame::InitPileOfCubes()
{
	unsigned short cubeAmount = 1000;
	myPileOfCubes.Init(cubeAmount);

	CU::Vector3f positionOffset = CU::Vector3f::Zero;

	for (unsigned int i = 0; i < cubeAmount; ++i)
	{
		//positionOffset = CU::Vector3f(myRandomizer.GetRandomValue(-0.5f, 0.5f), myRandomizer.GetRandomValue(-0.4f, 0.4f), myRandomizer.GetRandomValue(-0.2f, 0.2f));
		myPileOfCubes.Add(CHUGModel());
		myPileOfCubes[i].InitAsCube(positionOffset, CU::Vector3f(0.6f, 0.6f, 0.6f));
	}
}
