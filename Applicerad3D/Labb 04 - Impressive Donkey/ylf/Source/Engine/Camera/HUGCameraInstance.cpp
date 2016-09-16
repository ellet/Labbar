#include "stdafx.h"
#include "Camera/HUGCameraInstance.h"
#include "Camera/HUGCamera.h"

CHUGCameraInstance::CHUGCameraInstance()
{
	myCamera = nullptr;
}

CHUGCameraInstance::~CHUGCameraInstance()
{
	SAFE_DELETE(myCamera);
}

void CHUGCameraInstance::Init(const float aProjectionHeight, const float aProjectionWidth, const CU::Vector3f &aPosition)
{
	myCamera = new CHUGCamera(aProjectionHeight, aProjectionWidth, aPosition);
	//myCamera = new CHUGCamera();
	//myCamera->SetProjection(90.f, 90.f);
	//myCamera->SetPosition(aPosition);
}

const CU::Matrix44f & CHUGCameraInstance::GetProjection() const
{
	return myCamera->GetProjection();
}

const CU::Matrix44f & CHUGCameraInstance::GetCameraMatrix() const
{
	return myCamera->GetCameraMatrix();
}

void CHUGCameraInstance::MovePosition(const CU::Vector3f &aPosition)
{
	myCamera->SetPosition(myCamera->GetMyPosition() + aPosition);
}

void CHUGCameraInstance::IncreaseYaw(const float aDegrees)
{
	myCamera->IncreaseYaw(DEGRESS_TO_RADIANSF(aDegrees));
}

void CHUGCameraInstance::IncreasePitch(const float aDegrees)
{
	myCamera->IncreasePitch(DEGRESS_TO_RADIANSF(aDegrees));
}

void CHUGCameraInstance::IncreaseRoll(const float aDegrees)
{
	myCamera->IncreaseRoll(DEGRESS_TO_RADIANSF(aDegrees));
}
