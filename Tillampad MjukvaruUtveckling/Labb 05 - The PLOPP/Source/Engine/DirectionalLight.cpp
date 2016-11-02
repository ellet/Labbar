#include "stdafx.h"
#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : myDirection(Vector3f(0.f, -1.f, 0.f)), myColor(0.5f, 0.5f, 0.5f)
{
}


DirectionalLight::~DirectionalLight()
{
}

const Vector3f & DirectionalLight::GetDirection() const
{
	return myDirection;
}

const Vector3f & DirectionalLight::GetColor() const
{
	return myColor;
}

void DirectionalLight::SetDirection(const Vector3f & aDirection)
{
	myDirection = aDirection;
	myDirection.Normalize();
}

void DirectionalLight::SetColor(const Vector3f & aColor)
{
	myColor = aColor;
	Saturate();
}

void DirectionalLight::Saturate()
{
	if (myColor.x > 1.f)
	{
		myColor.x = 1.f;
	}
	else if (myColor.x < 0.f)
	{
		myColor.x = 0.f;
	}

	if (myColor.y > 1.f)
	{
		myColor.y = 1.f;
	}
	else if (myColor.y < 0.f)
	{
		myColor.y = 0.f;
	}

	if (myColor.z > 1.f)
	{
		myColor.z = 1.f;
	}
	else if (myColor.z < 0.f)
	{
		myColor.z = 0.f;
	}
}
