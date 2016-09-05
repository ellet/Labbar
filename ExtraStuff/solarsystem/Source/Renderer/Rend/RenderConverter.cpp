#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "StaticSprite.h"
#include <CU/Vectors/vector2.h>
#include <CU/Utility/Math/Isometric.h>

#include <CU/PostMaster/SingletonPostMaster.h>
#include "Rend/RenderCommand.h"
#include <CU/Camera/Camera2D.h>

#include <CU/Utility/DataHolder/SingletonDataHolder.h>

RenderConverter * RenderConverter::ourInstance = nullptr;

RenderConverter::RenderConverter()
{
}


RenderConverter::~RenderConverter()
{
}



void RenderConverter::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new RenderConverter();
	}
}

void RenderConverter::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void RenderConverter::Init(const CU::Vector2ui & aWindowSize)
{
	GetInstance().myRenderer.Init();
	GetInstance().myRenderer.SetWindowSize(aWindowSize);
	GetInstance().myWindowSize = aWindowSize;

	GetInstance().myLevelTileLayout = CU::Vector2ui(10, 10);
}

void RenderConverter::CalculateAndRenderSprite(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	CU::Vector2f newPos(aPosition);
	newPos.x /= 1920.f;//FLOATCAST(SingletonDataHolder::GetTargetResolution().x);
	newPos.y /= 1080.f; //FLOATCAST(SingletonDataHolder::GetTargetResolution().y);
	GetInstance().AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), newPos, aSpriteToRender.GetRenderPriority(), static_cast<USHORT>(aSpriteToRender.GetLayer()), aSpriteToRender.GetRenderData()));
}

void RenderConverter::RenderSpriteNormalized(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	GetInstance().AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aPosition, aSpriteToRender.GetRenderPriority(), static_cast<USHORT>(aSpriteToRender.GetLayer()), aSpriteToRender.GetRenderData()));
}

void RenderConverter::AddRenderCommand(RenderCommand & aRenderCommand)
{
	myRenderer.AddRenderCommand(aRenderCommand);
}

void RenderConverter::DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor /*= CU::Vector4f::One*/)
{
	GetInstance().myRenderer.DrawLine(aStartPosition, aEndPosition, aColor);
}

void RenderConverter::ClearCommands()
{
	GetInstance().myRenderer.ClearCommands();
}

void RenderConverter::SetShouldCull(const bool aCullingFlag)
{
	GetInstance().myRenderer.SetCull(aCullingFlag);
}

void RenderConverter::Draw()
{
	GetInstance().myRenderer.Draw();
}

void RenderConverter::SwapBuffers()
{
	GetInstance().myRenderer.SwapBuffer();
}
