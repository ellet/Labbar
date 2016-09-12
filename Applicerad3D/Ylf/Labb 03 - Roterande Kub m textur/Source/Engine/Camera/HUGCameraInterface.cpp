#include "stdafx.h"
#include "HUGCameraInterface.h"
#include "Camera/HUGCamera.h"

CHUGCameraInterface::CHUGCameraInterface()
{
	myCamera = nullptr;
}

CHUGCameraInterface::~CHUGCameraInterface()
{
	SAFE_DELETE(myCamera);
}

void CHUGCameraInterface::Init(const float aProjectionHeight, const float aProjectionWidth, const CU::Vector3f &aPosition)
{
	myCamera = new CHUGCamera(aProjectionHeight, aProjectionWidth, aPosition);
	//myCamera = new CHUGCamera();
	//myCamera->SetProjection(90.f, 90.f);
	//myCamera->SetPosition(aPosition);
}

const CU::Matrix44f & CHUGCameraInterface::GetProjection() const
{
	return myCamera->GetProjection();
}

const CU::Matrix44f & CHUGCameraInterface::GetCameraMatrix() const
{
	return myCamera->GetCameraMatrix();
}

void CHUGCameraInterface::MovePosition(const CU::Vector3f &aPosition)
{
	myCamera->SetPosition(myCamera->GetMyPosition() + aPosition);
}

void CHUGCameraInterface::IncreaseYaw(const float aDegrees)
{
	myCamera->IncreaseYaw(DEGRESS_TO_RADIANSF(aDegrees));
}

void CHUGCameraInterface::IncreasePitch(const float aDegrees)
{
	myCamera->IncreasePitch(DEGRESS_TO_RADIANSF(aDegrees));
}

void CHUGCameraInterface::IncreaseRoll(const float aDegrees)
{
	myCamera->IncreaseRoll(DEGRESS_TO_RADIANSF(aDegrees));
}
