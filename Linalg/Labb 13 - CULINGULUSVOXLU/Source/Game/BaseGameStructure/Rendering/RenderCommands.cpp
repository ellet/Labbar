#include "stdafx.h"
#include "RenderCommands.h"
#include <tga2d\sprite\sprite.h>
#include "../Game/Conversions/Conversions.h"


RenderCommands::RenderCommands()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;
}

void RenderCommands::Init(DX2D::CSprite * const aSprite, Vector3<float> aPosition, const WorldSpace * aWorldSpace, Vector4<float> aColour)
{
	myPosition = aPosition;
	mySprite = aSprite;
	myColour = aColour;

	myLocalSpace = aWorldSpace;
}

RenderCommands::~RenderCommands()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;
}

void RenderCommands::Render(const Camera & aCamera)
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

	myPosition /= myPosition.w;

	//myPosition.x += 0.5f;
	//myPosition.y += 0.5f;

	myPosition.x = (myPosition.x / 2) + 0.5f;
	myPosition.y = -(myPosition.y / 2) + 0.5f;


	if (tempScale > 0.05f &&
		myPosition.x > 0.f && myPosition.x < 1.f &&
		myPosition.y > 0.f && myPosition.y < 1.f)
	{
		Vector2f tempVector(myPosition.x, myPosition.y);

		DX2D::Vector2f temp;
		temp << tempVector;
		mySprite->SetPosition(temp);
		DX2D::CColor colour(myColour.r, myColour.g, myColour.b, myColour.a);
		mySprite->SetColor(colour);
		mySprite->SetSize(DX2D::Vector2f(tempScale, tempScale));
		mySprite->Render();
	}
}