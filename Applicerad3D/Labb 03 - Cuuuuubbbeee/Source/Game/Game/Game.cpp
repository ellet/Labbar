#include "stdafx.h"
#include "Game/Game.h"
#include <Engine/HUGEngine.h>
#include <dinput.h>

CGame::CGame()
{
	myCamera = Camera(900.f, 500.f, CU::Vector3f::Zero);
}


CGame::~CGame()
{
}

void CGame::Init()
{
	myCube.InitAsCube();
	//myTriangle.InitAsTriangle();
	
	myCamera.SetPosition({ 0.f, 0.4f, -1.f });
}

void CGame::Update()
{
	GET_INPUT.Update();
	
	float fakeDeltaTime = 0.0001f;
	
	float cameraSpeed = 0.5f;

	myCube.Update();
	

	if (GET_INPUT.GetKeyDown(DIK_D) == true)
	{
		myCamera.IncreaseRight(fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_A) == true)
	{
		myCamera.IncreaseRight(-fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_W) == true)
	{
		myCamera.IncreaseForward(fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_S) == true)
	{
		myCamera.IncreaseForward(-fakeDeltaTime * cameraSpeed);
	}

	if (GET_INPUT.GetKeyDown(DIK_RIGHTARROW) == true)
	{
		myCamera.IncreaseYaw(fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_LEFTARROW) == true)
	{
		myCamera.IncreaseYaw(-fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_UPARROW) == true)
	{
		myCamera.IncreasePitch(fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_DOWNARROW) == true)
	{
		myCamera.IncreasePitch(-fakeDeltaTime * cameraSpeed);
	}

	if (GET_INPUT.GetKeyDown(DIK_E) == true)
	{
		myCamera.IncreaseRoll(-fakeDeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_Q) == true)
	{
		myCamera.IncreaseRoll(fakeDeltaTime * cameraSpeed);
	}

}

void CGame::Render()
{
	myCube.Render(myCamera.GetInverse(), myCamera.GetProjection());
	//myTriangle.Render();
}
