#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{	
}


Camera::~Camera()
{
}

Camera::Camera(
	const float aProjectionHeight,
	const float aProjectionWidth,
	const CU::Vector3f &aPosition)
{
	/*
		PROJECTIONSTUFFS
	*/
	SetPosition(aPosition);

	myProjection = CU::Matrix44f::CreateProjectionMatrixLH(0.1f, 1000.f, DEGRESS_TO_RADIANSF(90.f), aProjectionHeight / aProjectionWidth);
}

CU::Matrix44f Camera::GetInverse() const
{
	CU::Matrix44<float> inverse(myTransformation);

	CU::Vector4<float> translation = inverse.GetPosition4();
	inverse.SetPosition(CU::Vector4<float>(0, 0, 0, 1.f));
	translation *= -1.f;
	translation.w = 1.f;
	inverse.Transpose();
	translation = translation * inverse;

	inverse.SetPosition(translation);
	return inverse;
}

const CU::Matrix44f& Camera::GetProjection() const
{
	return myProjection;
}

void Camera::IncreasePosition(CU::Vector3f aPosition)
{
	myTransformation.SetPosition(aPosition + myTransformation.GetPosition());
}

void Camera::IncreaseYaw(float aRadian)
{
	CU::Vector3f tempPosition(myTransformation.GetPosition());

	myTransformation.SetPosition(CU::Vector3f(0.f, 0.f, 0.f));

	myTransformation = myTransformation.CreateRotateAroundY(aRadian) * myTransformation;;

	myTransformation.SetPosition(tempPosition);
}

void Camera::IncreasePitch(float aRadian)
{
	CU::Vector3f tempPosition(myTransformation.GetPosition());

	myTransformation.SetPosition(CU::Vector3f(0.f, 0.f, 0.f));

	myTransformation = myTransformation.CreateRotateAroundX(aRadian) * myTransformation;

	myTransformation.SetPosition(tempPosition);
}

void Camera::IncreaseRoll(float aRadian)
{
	CU::Vector3f tempPosition(myTransformation.GetPosition());

	myTransformation.SetPosition(CU::Vector3f(0.f, 0.f, 0.f));

	myTransformation = myTransformation.CreateRotateAroundZ(aRadian) * myTransformation;;

	myTransformation.SetPosition(tempPosition);
}

void Camera::IncreaseForward(float aDelta)
{
	SetPosition(GetMyPosition() + (myTransformation.GetForward() * aDelta ));
}

void Camera::IncreaseRight(float aDelta)
{
	SetPosition(GetMyPosition() + (myTransformation.GetRight() * aDelta));
}

void Camera::SetPosition(CU::Vector3f aPosition)
{
	myTransformation.SetPosition(aPosition);
}

CU::Vector3f Camera::GetMyPosition() const
{
	return myTransformation.GetPosition();
}