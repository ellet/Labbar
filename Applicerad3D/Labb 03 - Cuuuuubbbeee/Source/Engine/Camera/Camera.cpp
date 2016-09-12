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

	myProjection = CU::Matrix44f::CreateProjectionMatrixLH(0.1f, 100.f, aProjectionWidth/aProjectionHeight, DEGRESS_TO_RADIANS(100.f));
}

CU::Matrix44f Camera::GetInverse() const
{
	/*Matrix44f temp(myTransformation);
	Vector4f tempPos = myTransformation.GetPosition4();
	temp.SetPosition(Vector4f(0.f, 0.f, 0.f, 1.f));

	temp.m12 = -temp.m12;
	temp.m21 = -temp.m21;
	
	tempPos = -tempPos;
	tempPos.w = -tempPos.w;

	temp.SetPosition(tempPos * temp);

	return temp;*/

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
	//aPosition = aPosition * myTransformation;

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