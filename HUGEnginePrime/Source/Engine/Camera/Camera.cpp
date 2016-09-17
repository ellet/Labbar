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
	const float aFoVAngle,
	const CU::Vector3f &aPosition)
{
	SetPosition(aPosition);

	myProjection = CU::Matrix44f::CreateProjectionMatrixLH(0.01f, 1000.f, aProjectionWidth / aProjectionHeight, aFoVAngle);
}

CU::Matrix44f Camera::GetInverse()
{
	UpdateTransformation();
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
	myPosition += aPosition;
	myTransformation.SetPosition(myPosition);
}

void Camera::IncreaseYaw(float aRadian)
{
	myRotation.RotateY(aRadian);
	UpdateTransformation();

}

void Camera::IncreasePitch(float aRadian)
{
	myRotation.RotateX(aRadian);
	UpdateTransformation();
}

void Camera::IncreaseRoll(float aRadian)
{
	myRotation.RotateZ(aRadian);
	UpdateTransformation();
}

void Camera::IncreaseForward(float aDelta)
{
	UpdateTransformation();
	SetPosition(GetMyPosition() + (myTransformation.GetForward() * aDelta ));
}

void Camera::IncreaseRight(float aDelta)
{
	UpdateTransformation();
	SetPosition(GetMyPosition() + (myTransformation.GetRight() * aDelta));
}

void Camera::SetPosition(CU::Vector3f aPosition)
{
	myPosition = aPosition;
	myTransformation.SetPosition(myPosition);
}

CU::Vector3f Camera::GetMyPosition() const
{
	return myPosition;
}

const CU::Matrix44f & Camera::GetTransformation() const
{
	return myTransformation;
}

void Camera::UpdateTransformation()
{
	myTransformation = myRotation.GenerateMatrix();
	myTransformation.SetPosition(myPosition);
}

