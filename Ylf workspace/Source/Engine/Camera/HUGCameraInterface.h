#pragma once
class CHUGCamera;

class CHUGCameraInterface
{
public:
	CHUGCameraInterface();
	~CHUGCameraInterface();

	void Init(const float aProjectionHeight,
		const float aProjectionWidth,
		const CU::Vector3f &aPosition);

	const CU::Matrix44f &GetProjection() const;
	const CU::Matrix44f &GetCameraMatrix() const;

	void MovePosition(const CU::Vector3f &aPosition);

	void IncreaseYaw(const float aDegrees);

	void IncreasePitch(const float aDegrees);

	void IncreaseRoll(const float aDegrees);

private:
	CHUGCamera * myCamera;
};

