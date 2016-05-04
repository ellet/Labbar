#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	myRotation = 0;
	
}


Camera::~Camera()
{
}

Camera::Camera(
	const float aProjectionHeight,
	const float aProjectionWidth,
	const Vector2f &aPosition)
{
	/*
		PROJECTIONSTUFFS
	*/
	SetPosition(aPosition);

	myProjection.m11 = (2.f / aProjectionWidth);
	myProjection.m12 = 0.f;
	myProjection.m13 = 0.f;

	myProjection.m21 = 0.f;
	myProjection.m22 = (2.f / aProjectionHeight);
	myProjection.m23 = 0.f;

	myProjection.m31 = 0.f;
	myProjection.m32 = 0.f;
	myProjection.m33 = 1.f;

}

Matrix33f Camera::GetInverse() const
{
	Matrix33f temp(myTransformation);
	Vector3f tempPos = myTransformation.GetPosition3();
	temp.SetPosition(Vector3f(0.f, 0.f, 1.f));

	temp.m12 = -temp.m12;
	temp.m21 = -temp.m21;

	tempPos = -tempPos;

	temp.SetPosition(tempPos * temp);

	return temp;
}

const Matrix33f& Camera::GetProjection() const
{
	return myProjection;
}

void Camera::IncreasePosition(Vector2f aPosition)
{
	aPosition = aPosition * myTransformation;

	myTransformation.SetPosition(aPosition);
}

void Camera::IncreaseRotation(float aRadian)
{
	//myRotation += aRadian;
	myTransformation.Rotate2D(aRadian);//(myRotation);
}



void Camera::SetPosition(Vector2f aPosition)
{
	myTransformation.SetPosition(aPosition);
}

Vector2f Camera::GetMyPosition() const
{
	return myTransformation.GetPosition();
}