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
	CU::TimeManager::Update();
	
	const float DeltaTime = CU::TimeManager::GetDeltaTime().GetSeconds();
	
	float cameraSpeed = 0.5f;

	myCube.Update(CU::TimeManager::GetDeltaTime().GetSeconds());
	

	if (GET_INPUT.GetKeyDown(DIK_D) == true)
	{
		myCamera.IncreaseRight(DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_A) == true)
	{
		myCamera.IncreaseRight(-DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_W) == true)
	{
		myCamera.IncreaseForward(DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_S) == true)
	{
		myCamera.IncreaseForward(-DeltaTime * cameraSpeed);
	}

	if (GET_INPUT.GetKeyDown(DIK_RIGHTARROW) == true)
	{
		myCamera.IncreaseYaw(DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_LEFTARROW) == true)
	{
		myCamera.IncreaseYaw(-DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_UPARROW) == true)
	{
		myCamera.IncreasePitch(DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_DOWNARROW) == true)
	{
		myCamera.IncreasePitch(-DeltaTime * cameraSpeed);
	}

	if (GET_INPUT.GetKeyDown(DIK_E) == true)
	{
		myCamera.IncreaseRoll(-DeltaTime * cameraSpeed);
	}
	if (GET_INPUT.GetKeyDown(DIK_Q) == true)
	{
		myCamera.IncreaseRoll(DeltaTime * cameraSpeed);
	}

}

void CGame::Render()
{
	myCube.Render(myCamera.GetInverse(), myCamera.GetProjection());
}
