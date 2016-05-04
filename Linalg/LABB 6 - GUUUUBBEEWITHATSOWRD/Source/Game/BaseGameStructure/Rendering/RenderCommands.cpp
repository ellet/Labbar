#include "stdafx.h"
#include "RenderCommands.h"
#include <tga2d\sprite\sprite.h>
#include "../Game/Conversions/Conversions.h"


RenderCommands::RenderCommands()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;
}

void RenderCommands::Init(DX2D::CSprite * const aSprite, Vector2<float> aPosition, const WorldSpace * aWorldSpace)
{
	myPosition = aPosition;
	mySprite = aSprite;

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
	Matrix33f worldsData = Matrix33f::Identity;

	while (currentSpace != nullptr)
	{
		//myPosition = myPosition * currentSpace->GetSpaceData();
		worldsData = worldsData * currentSpace->GetSpaceData();

		currentSpace = currentSpace->GetParent();
	}

	//Vector2f tempderp = myPosition;
	worldsData = worldsData * aCamera.GetInverse();
	myPosition = myPosition * worldsData;

	myPosition.x += 0.5f;
	myPosition.y += 0.5f;
	

	DX2D::Vector2f temp;
	temp << myPosition;
	mySprite->SetPosition(temp);
	mySprite->Render();
}