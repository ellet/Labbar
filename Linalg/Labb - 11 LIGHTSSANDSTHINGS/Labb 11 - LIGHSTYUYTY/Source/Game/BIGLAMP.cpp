#include "stdafx.h"
#include "BIGLAMP.h"
#include <Matriser/matrix33.h>
#include <Macros.h>

BIGLAMP * BIGLAMP::ourInstance = nullptr;





void BIGLAMP::Create(const Vector3f aDirection, const Vector4f aColor)
{
	if (ourInstance == nullptr)
	{
		ourInstance = new BIGLAMP(aDirection, aColor);
	}
}

void BIGLAMP::Destroy()
{
	if (ourInstance != nullptr)
	delete ourInstance;
	ourInstance = nullptr;
}

BIGLAMP::BIGLAMP(const Vector3f aDirection, const Vector4f aColor)
{
	myDirection = aDirection;
	myColor = aColor;
}


BIGLAMP::~BIGLAMP()
{
}

void BIGLAMP::InsideRotateLight(const float aDeltaTime)
{
	Vector3f tempPosition = myDirection * Matrix33f::CreateRotateAroundY(DEGRESS_TO_RADIANSF(25.f));
	Vector3f difference = myDirection - tempPosition;
	myDirection += difference * aDeltaTime;
}