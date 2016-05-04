#pragma once
#include "../Vectors/Vector.h"
#include "../Matriser/matrix44.h"

class Camera
{
public:
	Camera();
	~Camera();

	Camera(
		const float aProjectionHeight,
		const float aProjectionWidth,
		const Vector3f &aPosition);

	Matrix44f GetInverse(void) const;

	const Matrix44f &GetProjection(void) const;

	void IncreasePosition(Vector3f aPosition);

	void IncreaseYaw(float aRadian);

	void IncreasePitch(float aRadian);

	void IncreaseRoll(float aRadian);

	void IncreaseForward(float aDelta);

	void IncreaseRight(float aDelta);

	void SetPosition(Vector3f aPosition);

	Vector3f GetMyPosition() const;

private:
	Matrix44f myTransformation;
	Matrix44f myProjection;
};

