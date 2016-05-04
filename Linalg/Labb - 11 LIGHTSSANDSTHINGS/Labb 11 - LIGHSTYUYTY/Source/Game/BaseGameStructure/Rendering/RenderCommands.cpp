#include "stdafx.h"
#include "RenderCommands.h"
#include <tga2d\sprite\sprite.h>
#include "../Game/Conversions/Conversions.h"
#include "../../BIGLAMP.h"


const float SpecularPower = 24.f;

RenderCommands::RenderCommands()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;
}

void RenderCommands::Init(DX2D::CSprite * const aSprite, Vector3<float> aPosition, const WorldSpace * aWorldSpace, const Vector4<float> aColour, const Vector3f aNormal)
{
	myPosition = aPosition;
	mySprite = aSprite;
	myColour = aColour;
	myNormal = aNormal;

	myLocalSpace = aWorldSpace;
}

RenderCommands::~RenderCommands()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;
}

RenderSolution RenderCommands::Render(const Camera & aCamera)
{
	const WorldSpace * currentSpace = myLocalSpace;
	Matrix44f worldsData = Matrix44f::Identity;

	while (currentSpace != nullptr)
	{
		worldsData = worldsData * currentSpace->GetSpaceData();

		currentSpace = currentSpace->GetParent();
	}
	
	worldsData = worldsData * aCamera.GetInverse();
	myPosition = (myPosition * worldsData) * aCamera.GetProjection();

	float tempScale =  1 / myPosition.w;

	float zValue = myPosition.z;

	myPosition /= myPosition.w;

	//myPosition.x += 0.5f;
	//myPosition.y += 0.5f;

	myPosition.x = (myPosition.x / 2) + 0.5f;
	myPosition.y = -(myPosition.y / 2) + 0.5f;

	bool shouldRender = (aCamera.GetMyPosition() - myPosition).Dot(myNormal) > 0;

	if (tempScale > 0.05f &&
		myPosition.x > 0.f && myPosition.x < 1.f &&
		myPosition.y > 0.f && myPosition.y < 1.f &&
		shouldRender == true)
	{
		Vector2f tempVector(myPosition.x, myPosition.y);

		DX2D::Vector2f temp;
		temp << tempVector;
		mySprite->SetPosition(temp);
		mySprite->SetColor(CalculateLight(aCamera));
		mySprite->SetSize(DX2D::Vector2f(tempScale, tempScale));
		//mySprite->Render();
		RenderSolution tempRender;
		tempRender.myZPosition = zValue;
		tempRender.mySprite = mySprite;
		return tempRender;
	}

	RenderSolution tempRender;
	tempRender.myZPosition = zValue;
	tempRender.mySprite = nullptr;
	return tempRender;
}

DX2D::CColor RenderCommands::CalculateLight(const Camera & aCamera)
{
	Vector3f LightDirection = BIGLAMP::GetDirection();
	Vector4f LightColor = BIGLAMP::GetColor();

	Vector3f CameraPosition = aCamera.GetMyPosition();
	Vector3f EyeDistance = CameraPosition - myPosition;

	EyeDistance += -LightDirection;
	EyeDistance = EyeDistance / 2.f;
	Vector3f halfAngleVector(EyeDistance.GetNormalized());

	float normalLightDirDot = myNormal.Dot(-LightDirection);
	normalLightDirDot = CLAMPYCLAMPY(normalLightDirDot);

	Vector4f diffuse = MultiplyVector4((myColour * normalLightDirDot), LightColor);

	float halfVectorNormal = halfAngleVector.Dot(myNormal);
	halfVectorNormal = CLAMPYCLAMPY(halfVectorNormal);

	halfVectorNormal = pow(halfVectorNormal, SpecularPower);

	Vector4f Specular = LightColor * halfVectorNormal;

	Vector4f DACOLOR = diffuse + Specular;

	DACOLOR.r = CLAMPYCLAMPY(DACOLOR.r);
	DACOLOR.g = CLAMPYCLAMPY(DACOLOR.g);
	DACOLOR.b = CLAMPYCLAMPY(DACOLOR.b);

	DX2D::CColor tempColor(DACOLOR.r, DACOLOR.g, DACOLOR.b, 1.f);
	return tempColor;
}

float RenderCommands::CLAMPYCLAMPY(const float aValue, const float aMin /*= 0.f*/, const float aMax /*= 1.f*/)
{
	return std::min(aMax, std::max(aMin, aValue));
}

Vector4f RenderCommands::MultiplyVector4(Vector4f aFirstVector, Vector4f aSecondVector)
{
	return Vector4f(aFirstVector.x * aSecondVector.x,
		aFirstVector.y * aSecondVector.y,
		aFirstVector.z * aSecondVector.z,
		aFirstVector.w * aSecondVector.w);
}