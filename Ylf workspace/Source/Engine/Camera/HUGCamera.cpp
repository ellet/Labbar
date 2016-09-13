#include "stdafx.h"
#include "Camera/HUGCamera.h"
#include "CU/Macros/Macros.h"

CHUGCamera::CHUGCamera()
{	
}


CHUGCamera::~CHUGCamera()
{
}

CHUGCamera::CHUGCamera(
	const float aProjectionHeight,
	const float aProjectionWidth,
	const CU::Vector3f &aPosition)
{
	SetPosition(aPosition);

	myProjection = CU::Matrix44f::CreateProjectionMatrixLH(0.1f, 100.f, aProjectionWidth/aProjectionHeight, DEGRESS_TO_RADIANS(100.f));
}

CU::Matrix44f CHUGCamera::GetInverse() const
{
	CU::Matrix44f inverse(myTransformation);

	CU::Vector4f translation = inverse.GetPosition4();
	inverse.SetPosition(CU::Vector4f(0, 0, 0, 1.f));
	translation *= -1.f;
	translation.w = 1.f;
	inverse.Transpose();
	translation = translation * inverse;

	inverse.SetPosition(translation);
	return inverse;
}

void CHUGCamera::SetProjection(const float aProjectionHeight, const float aProjectionWidth)
{
	myProjection = CU::Matrix44f::CreateProjectionMatrixLH(0.1f, 100.f, aProjectionWidth / aProjectionHeight, DEGRESS_TO_RADIANS(100.f));
}

const CU::Matrix44f& CHUGCamera::GetProjection() const
{
	return myProjection;
}

const CU::Matrix44f & CHUGCamera::GetCameraMatrix() const
{
	return myTransformation;
}

void CHUGCamera::IncreasePosition(CU::Vector3f aPosition)
{
	myTransformation.SetPosition(aPosition + myTransformation.GetPosition());
}

void CHUGCamera::IncreaseYaw(float aRadian)
{
	CU::Vector3f tempPosition(myTransformation.GetPosition());

	myTransformation.SetPosition(CU::Vector3f(0.f, 0.f, 0.f));

	myTransformation = myTransformation.CreateRotateAroundY(aRadian) * myTransformation;;

	myTransformation.SetPosition(tempPosition);
}

void CHUGCamera::IncreasePitch(float aRadian)
{
	CU::Vector3f tempPosition(myTransformation.GetPosition());

	myTransformation.SetPosition(CU::Vector3f(0.f, 0.f, 0.f));

	myTransformation = myTransformation.CreateRotateAroundX(aRadian) * myTransformation;

	myTransformation.SetPosition(tempPosition);
}

void CHUGCamera::IncreaseRoll(float aRadian)
{
	CU::Vector3f tempPosition(myTransformation.GetPosition());

	myTransformation.SetPosition(CU::Vector3f(0.f, 0.f, 0.f));

	myTransformation = myTransformation.CreateRotateAroundZ(aRadian) * myTransformation;;

	myTransformation.SetPosition(tempPosition);
}

void CHUGCamera::IncreaseForward(float aDelta)
{
	SetPosition(GetMyPosition() + (myTransformation.GetForward() * aDelta ));
}

void CHUGCamera::IncreaseRight(float aDelta)
{
	SetPosition(GetMyPosition() + (myTransformation.GetRight() * aDelta));
}

void CHUGCamera::SetPosition(CU::Vector3f aPosition)
{
	myTransformation.SetPosition(aPosition);
}

CU::Vector3f CHUGCamera::GetMyPosition() const
{
	return myTransformation.GetPosition();
}