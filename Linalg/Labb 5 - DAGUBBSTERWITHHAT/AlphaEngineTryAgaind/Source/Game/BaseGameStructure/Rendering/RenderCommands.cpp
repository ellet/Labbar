#include "stdafx.h"
#include "RenderCommands.h"
#include <tga2d\sprite\sprite.h>
#include "../Game/Conversions/Conversions.h"


RenderCommands::RenderCommands()
{
	mySprite = nullptr;
	myLocalSpace = nullptr;
}

void RenderCommands::Init(DX2D::CSprite * const aSprite, Vector2<float> aPosition, WorldSpace * aWorldSpace)
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

void RenderCommands::Render()
{
	WorldSpace * currentSpace = myLocalSpace;
	while (currentSpace != nullptr)
	{
		myPosition = myPosition * currentSpace->GetSpaceData();

		currentSpace = currentSpace->GetParent();
	}

	DX2D::Vector2f temp;
	temp << myPosition;
	mySprite->SetPosition(temp);
	mySprite->Render();
}