#pragma once
#include "Camera/Camera.h"

class CHUGCameraManager
{
public:
	CHUGCameraManager();
	~CHUGCameraManager();

	const Camera & GetActiveCamera() const;
	const Camera & GetCameraAtIndex(const unsigned short anIndex) const;
	void SetActiveCamera(const unsigned short anIndex);

	void CreateCamera(
		const float aProjectionHeight,
		const float aProjectionWidth, 
		const CU::Vector3f & aPosition = CU::Vector3f::Zero,
		const float aFoVAngle = DEGRESS_TO_RADIANSF(90.f));

private:
	CU::GrowingArray<Camera> myCameras;
	unsigned short myActiveCamera;
};

