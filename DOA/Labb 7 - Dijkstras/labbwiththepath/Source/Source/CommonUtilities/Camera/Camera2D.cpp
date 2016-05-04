#include "Camera2D.h"

Camera2D::Camera2D()
{
	myShaking = false;
	myShakeDuration = 0;
	myShakeForce = 1.f;
}

Camera2D::~Camera2D()
{
}

void Camera2D::StopShaking()
{
	myShaking = false;
	myShakeDuration = 0;
}

void Camera2D::Init(const Vector2<float>* aResolutionPtr, const Vector2<float>& aPosition)
{
	myResolutionPtr = aResolutionPtr;
	myProjection.myMatrix[0] = 2.f / aResolutionPtr->x;
	myProjection.myMatrix[4] = 2.f / aResolutionPtr->y;
	myOrientation.myMatrix[6] = aPosition.x;
	myOrientation.myMatrix[7] = aPosition.y;
	myResolutionScale = aResolutionPtr->y / 720.f;
	myTargetPos = aPosition;

	myRandomizer.SetMinMax(-0.1f, 0.1f);
}

void Camera2D::Update(float aDelta)
{
	Vector2<float> pos = myOrientation.GetPosition();
	pos += (myTargetPos - pos) * aDelta * 5.f;

	if (myShaking == true)
	{
		myShakeDuration -= aDelta;
		if (myShakeDuration < 0)
		{
			myShaking = false;
		}

		pos.x += myRandomizer.GetRandomValue(-myShakeForce, myShakeForce);
		pos.y += myRandomizer.GetRandomValue(-myShakeForce, myShakeForce);
	}

	myOrientation.SetPosition(pos);
}

void Camera2D::Shake(const float aDuration, const float aForce)
{
	myShakeDuration = aDuration;
	myShakeForce = aForce;
	myShaking = true;
}

const Matrix33<float> Camera2D::GetInverse() const
{
	
	Vector3<float> translation(-myOrientation.myMatrix[6], -myOrientation.myMatrix[7], 1);
	Matrix33<float> inverse(myOrientation);
	inverse.myMatrix[6] = 0;
	inverse.myMatrix[7] = 0;
	inverse = inverse.Transpose();
	translation *= inverse;
	inverse.myMatrix[6] = translation.x;
	inverse.myMatrix[7] = translation.y;
	return inverse;
}

const Vector2<float> Camera2D::GetScreenOffset() const
{
	return (GetPosition() - (*myResolutionPtr / 2.f)) * myResolutionScale;
}

void Camera2D::Move(Vector3<float> aVector)
{
	aVector *= myOrientation;
	myOrientation.myMatrix[6] += aVector.x;
	myOrientation.myMatrix[7] += aVector.y;
}

void Camera2D::Zoom(float aFraction)
{
	myProjection.myMatrix[0] *= aFraction;
	myProjection.myMatrix[4] *= aFraction;
}

void Camera2D::SetProjection()
{
	myProjection.myMatrix[0] = 2.f / myResolutionPtr->x;
	myProjection.myMatrix[4] = 2.f / myResolutionPtr->y;
}