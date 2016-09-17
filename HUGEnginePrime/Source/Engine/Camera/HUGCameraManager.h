#pragma once
#include "Camera/Camera.h"

class CHUGCameraManager
{
public:
	CHUGCameraManager();
	~CHUGCameraManager();

	const Camera & GetActiveCamera() const;
	Camera & GetCameraAtIndex(const unsigned short anIndex);
	void SetActiveCamera(const unsigned short anIndex);

	void CreateCamera(
		const float aProjectionHeight,
		const float aProjectionWidth, 
		const CU::Vector3f & aPosition = CU::Vector3f::Zero,
		const float aFoVAngle = DEGRESS_TO_RADIANSF(90.f));

	void UpdateProjections(const CU::Vector2ui & aNewProjectionSize);

private:
	CU::GrowingArray<Camera> myCameras;
	CU::Matrix44f myProjection;

	unsigned short myActiveCamera;
};

