#include "stdafx.h"
#include "RenderCommand.h"
#include <tga2d/sprite/sprite.h>

//const USHORT TileWidth = 10;

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
}

RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aRenderPriority, const USHORT aLayer, const RenderData & aRenderData)
	: mySprite(&aSpriteToRender),
	myPosition(aPosition),
	myRenderData(aRenderData)
{
	myRenderPriority = aRenderPriority;
	myLayer = aLayer;
}

RenderCommand::~RenderCommand()
{
}


void RenderCommand::Render(const CU::Vector2f & aWindowSize) const
{
	DX2D::Vector2f tempPosition(myPosition.x, myPosition.y);
	DX2D::CColor tempColor(myRenderData.myColor.r, myRenderData.myColor.g, myRenderData.myColor.b, myRenderData.myColor.a);
	//DX2D::Vector2f tempSize(myRenderData.mySize, myRenderData.mySize);
	DX2D::Vector2f tempSize(mySprite->GetImageSize().x / aWindowSize.x, mySprite->GetImageSize().y / aWindowSize.y);
	tempSize *= myRenderData.mySize;

	mySprite->SetSize(tempSize);	
	mySprite->SetRotation(myRenderData.myRotation);
	mySprite->SetColor(tempColor);
	mySprite->SetPosition(tempPosition);
	mySprite->Render();
}