#pragma once


class Camera
{
public:
	Camera();
	~Camera();

	Camera(
		const float aProjectionHeight,
		const float aProjectionWidth,
		const float aFoVAngle = M_PI_2,
		const CU::Vector3f &aPosition = CU::Vector3f::Zero);

	CU::Matrix44f GetInverse(void);

	const CU::Matrix44f &GetProjection(void) const;

	void IncreasePosition(CU::Vector3f aPosition);

	void IncreaseYaw(float aRadian);

	void IncreasePitch(float aRadian);

	void IncreaseRoll(float aRadian);

	void IncreaseForward(float aDelta);

	void IncreaseRight(float aDelta);

	void SetPosition(CU::Vector3f aPosition);

	CU::Vector3f GetMyPosition() const;

	const CU::Matrix44f & GetTransformation() const;

private:
	void UpdateTransformation();

	CU::Quaternion myRotation;
	CU::Vector3f myPosition;

	CU::Matrix44f myTransformation;
	CU::Matrix44f myProjection;
};

