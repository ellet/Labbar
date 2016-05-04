#pragma once
#include "../CommonUtilities/Vectors/Vector.h"
#include "../CommonUtilities/Matriser/matrix33.h"

class Camera
{
public:
	Camera();
	~Camera();

	Camera(
		const float aProjectionHeight,
		const float aProjectionWidth,
		const Vector2f &aPosition);

	Matrix33f GetInverse(void) const;

	const Matrix33f &GetProjection(void) const;

	void IncreasePosition(Vector2f aPosition);
	void IncreaseRotation(float aRadian);

	void SetPosition(Vector2f aPosition);

	Vector2f GetMyPosition() const;

private:
	Matrix33f myTransformation;
	float myRotation;
	Matrix33f myProjection;
};

