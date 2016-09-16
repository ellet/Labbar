#include "stdafx.h"
#include "HUGCameraController.h"
//#include <CU/Systems/MainSingleton/MainSingleton.h>
//#include <dinput.h>
//
//CHUGCameraController::CHUGCameraController()
//{
//	myCamera = myCameraInstance
//	myCameraSpeed = 5.f;
//	myCameraRotationSpeed = 100.f;
//}
//
//
//CHUGCameraController::~CHUGCameraController()
//{
//}
//
//void CHUGCameraController::Update()
//{
//	const float deltaTime = GET_DELTA_SECONDS;
//
//	CU::Vector3f tempToAddCameraPosition = CU::Vector3f::Zero;
//
//	MoveLeft(deltaTime);
//	MoveRight(deltaTime);
//	MoveForward(deltaTime);
//	MoveBackwards(deltaTime);
//	MoveUp(deltaTime);
//	MoveDown(deltaTime);
//
//	if (GET_INPUT.GetKeyDown(DIK_UPARROW) == true)
//	{
//		myCamera.IncreasePitch(-myCameraRotationSpeed * deltaTime);
//	}
//	else if (GET_INPUT.GetKeyDown(DIK_DOWNARROW) == true)
//	{
//		myCamera.IncreasePitch(myCameraRotationSpeed * deltaTime);
//	}
//
//	if (GET_INPUT.GetKeyDown(DIK_RIGHTARROW) == true)
//	{
//		myCamera.IncreaseYaw(myCameraRotationSpeed * deltaTime);
//	}
//	else if (GET_INPUT.GetKeyDown(DIK_LEFTARROW) == true)
//	{
//		myCamera.IncreaseYaw(-myCameraRotationSpeed * deltaTime);
//	}
//
//	myCamera.MovePosition(tempToAddCameraPosition);
//}
//
//void CHUGCameraController::MoveLeft(const float aDeltaTime)
//{
//	if (GET_INPUT.GetKeyDown(DIK_A) == true)
//	{
//		tempToAddCameraPosition.x -= myCameraSpeed * aDeltaTime;
//	}
//}
//
//void CHUGCameraController::MoveRight(const float aDeltaTime)
//{
//	if (GET_INPUT.GetKeyDown(DIK_D) == true)
//	{
//		tempToAddCameraPosition.x += myCameraSpeed * aDeltaTime;
//	}
//}
//
//void CHUGCameraController::MoveForward(const float aDeltaTime)
//{
//	if (GET_INPUT.GetKeyDown(DIK_Q) == true)
//	{
//		tempToAddCameraPosition.z += myCameraSpeed * aDeltaTime;
//	}
//}
//
//void CHUGCameraController::MoveBackwards(const float aDeltaTime)
//{
//	if (GET_INPUT.GetKeyDown(DIK_E) == true)
//	{
//		tempToAddCameraPosition.z -= myCameraSpeed * aDeltaTime;
//	}
//}
//
//void CHUGCameraController::MoveUp(const float aDeltaTime)
//{
//	if (GET_INPUT.GetKeyDown(DIK_W) == true)
//	{
//		tempToAddCameraPosition.y += myCameraSpeed * aDeltaTime;
//	}
//}
//
//void CHUGCameraController::MoveDown(const float aDeltaTime)
//{
//	if (GET_INPUT.GetKeyDown(DIK_S) == true)
//	{
//		tempToAddCameraPosition.y -= myCameraSpeed * aDeltaTime;
//	}
//}
