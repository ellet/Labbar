#include "stdafx.h"
#include "RenderCommand.h"
#include <tga2d/sprite/sprite.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
	
}


RenderCommand::RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aPriority, const unsigned short aLayer, const RenderData & aRenderData)
	: mySprite(&aSpriteToRender),
	myPosition(aPosition),
	myRenderData(aRenderData)
{
	myRenderPriority = aPriority;
	myLayer = aLayer;
}

USHORT RenderCommand::GetLayer()
{
	return myLayer;
}

float RenderCommand::GetPriority()
{
	return myRenderPriority;
}



RenderCommand::~RenderCommand()
{
}

void RenderCommand::Render() const
{
	
	DX2D::CColor tempColor(myRenderData.myColor.r, myRenderData.myColor.g, myRenderData.myColor.b, myRenderData.myColor.a);

	
	DX2D::Vector2f tempPosition = {myPosition.x, myPosition.y};


	if (mySprite != nullptr)
	{
		DL_ASSERT(myRenderData.mySizeInPixels != CU::Vector2f::Zero, "Sprite size is zero during rendering");

		float normalizedWindowSizeX = myRenderData.mySizeInPixels.x / (1920.f * (9.f / 16.f));//FLOATCAST(SingletonDataHolder::GetTargetResolution().x) *SingletonDataHolder::GetTargetResolutionRatio();
		float normalizedWindowSizeY = myRenderData.mySizeInPixels.y / 1080.f;//FLOATCAST(SingletonDataHolder::GetTargetResolution().y);

		//float normalizedWindowSizeX = 1.f;
		//float normalizedWindowSizeY = 1.f;

		//float renderScale = FLOATCAST(SingletonDataHolder::GetTargetResolution().y) / (1080.f);
		float renderScale = 1.f;

		DX2D::Vector2f tempSize(normalizedWindowSizeX * renderScale * myRenderData.mySize.x, normalizedWindowSizeY * renderScale * myRenderData.mySize.y);
		//DX2D::Vector2f tempSize(1.f, 1.f);

		mySprite->SetColor(tempColor);
		mySprite->SetPosition(tempPosition);
		mySprite->SetSize(tempSize);

		mySprite->Render();
	}
}