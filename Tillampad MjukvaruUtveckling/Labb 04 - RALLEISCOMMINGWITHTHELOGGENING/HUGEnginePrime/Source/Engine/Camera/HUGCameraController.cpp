#include "stdafx.h"
#include "Camera/HUGCameraController.h"
#include "Engine/HUGEngine.h"
#include "Camera/HUGCameraManager.h"
#include "Camera/Camera.h"


CHUGCameraController::CHUGCameraController()
{
	myCameraIndex = 0;
}


CHUGCameraController::~CHUGCameraController()
{
}

void CHUGCameraController::IncreasePosition(CU::Vector3f aPosition)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).IncreasePosition(aPosition);
}

void CHUGCameraController::IncreaseYaw(float aRadian)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).IncreaseYaw(aRadian);
}

void CHUGCameraController::IncreasePitch(float aRadian)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).IncreasePitch(aRadian);
}

void CHUGCameraController::IncreaseRoll(float aRadian)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).IncreaseRoll(aRadian);
}

void CHUGCameraController::IncreaseForward(float aDelta)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).IncreaseForward(aDelta);
}

void CHUGCameraController::IncreaseRight(float aDelta)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).IncreaseRight(aDelta);
}

void CHUGCameraController::SetPosition(CU::Vector3f aPosition)
{
	CHUGEngineSingleton::GetCameraManager().GetCameraAtIndex(myCameraIndex).SetPosition(aPosition);
}
