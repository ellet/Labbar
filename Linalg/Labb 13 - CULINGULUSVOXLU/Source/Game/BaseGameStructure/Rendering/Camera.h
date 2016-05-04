#pragma once
#include "../CommonUtilities/Vectors/Vector.h"
#include "../CommonUtilities/Matriser/matrix44.h"


namespace Intersection3D
{
	class Fov90Frustum;
}

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

	const Intersection3D::Fov90Frustum & GetFrustum();

private:
	Matrix44f myTransformation;
	Matrix44f myProjection;

	Intersection3D::Fov90Frustum * myFrustum;
};

