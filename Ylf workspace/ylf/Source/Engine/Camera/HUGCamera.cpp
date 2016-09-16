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
	const float aWindowWidth,
	const float aWindowHeight,
	const CU::Vector3f &aPosition)
{
	SetPosition(aPosition);

	SetProjection(aWindowWidth, aWindowHeight);
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

void CHUGCamera::SetProjection(const float aWindowWidth, const float aWindowHeight)
{
	myProjection = CU::Matrix44f::CreateProjectionMatrixLH(0.001f, 1000.f, (aWindowWidth / aWindowHeight), M_PI_2);
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