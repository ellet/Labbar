#pragma once
#include "CU/Math/Vectors/vector3.h"
#include "CU/Math/Matriser/matrix44.h"
#include "CU/Math/Quaternion/Quaternion.h"

class CHUGCamera
{
public:
	CHUGCamera();
	~CHUGCamera();

	CHUGCamera(
		const float aWindowWidth,
		const float aWindowHeight,
		const CU::Vector3f &aPosition);

	CU::Matrix44f GetInverse(void) const;

	void SetProjection(const float aWindowWidth,
		const float aWindowHeight);

	const CU::Matrix44f &GetProjection() const;
	const CU::Matrix44f &GetCameraMatrix() const;

	void IncreasePosition(CU::Vector3f aPosition);

	void IncreaseYaw(float aRadian);

	void IncreasePitch(float aRadian);

	void IncreaseRoll(float aRadian);

	void SetPosition(CU::Vector3f aPosition);

	CU::Vector3f GetMyPosition() const;

private:
	void UpdateTransformation();
	CU::Quaternion myRotation;
	CU::Vector3f myPosition;
	CU::Matrix44f myTransformation;
	CU::Matrix44f myProjection;
};

