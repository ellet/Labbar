#include "stdafx.h"
#include "Camera/HUGCameraManager.h"


CHUGCameraManager::CHUGCameraManager()
{
	myCameras.Init(2);
	myActiveCamera = 0;
}

CHUGCameraManager::~CHUGCameraManager()
{
}

const Camera & CHUGCameraManager::GetActiveCamera() const
{
	return myCameras[myActiveCamera];
}

Camera & CHUGCameraManager::GetCameraAtIndex(const unsigned short anIndex)
{
	return myCameras[anIndex];
}

void CHUGCameraManager::SetActiveCamera(const unsigned short anIndex)
{
	myActiveCamera = anIndex;
}

void CHUGCameraManager::CreateCamera(
	const float aProjectionHeight, 
	const float aProjectionWidth, 
	const CU::Vector3f & aPosition /*= CU::Vector3f::Zero*/, 
	const float aFoVAngle /*= DEGRESS_TO_RADIANSF(90.f)*/)
{
	Camera prettyCamera(aProjectionHeight, aProjectionWidth, aFoVAngle, aPosition);
	myCameras.Add(prettyCamera);
}

void CHUGCameraManager::UpdateProjections(const CU::Vector2ui & aNewProjectionSize)
{
	for (unsigned short iCamera = 0; iCamera < myCameras.Size(); ++iCamera)
	{
		myCameras[iCamera].UpdateProjection(CU::Vector2f(static_cast<float>(aNewProjectionSize.x), static_cast<float>(aNewProjectionSize.y)));
	}
}
