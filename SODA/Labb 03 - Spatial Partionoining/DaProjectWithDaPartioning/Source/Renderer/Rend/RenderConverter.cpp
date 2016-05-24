#include "stdafx.h"
#include "RenderConverter.h"
#include <tga2d/sprite/sprite.h>
#include "StaticSprite.h"
#include <CU/Vectors/vector2.h>
#include <CU/Utility/Math/Isometric.h>
#include <Message/LevelTileMetricsMessage.h>
#include <PostMaster/SingletonPostMaster.h>
#include "Rend/RenderCommand.h"

RenderConverter * RenderConverter::ourInstance = nullptr;



//const float TileWidth = 10;
const float TileSize = 128.f;
const float TileSizeHalf = 64.f;

RenderConverter::RenderConverter()
{
}


RenderConverter::~RenderConverter()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eLevelTileLayoutSettings, *this);
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

	GetInstance().myLevelTileLayout = CU::Vector2ui(10, 10);

	SingletonPostMaster::AddReciever(RecieverTypes::eLevelTileLayoutSettings, GetInstance());
}


void RenderConverter::CalculateAndRenderIso(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	RenderData tempRenderData(aSpriteToRender.GetColor());

	GetInstance().myRenderer.AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aPosition, 100.f, static_cast<USHORT>(aSpriteToRender.GetLayer()), tempRenderData));
}

void RenderConverter::CalculateAndRenderSprite(const StaticSprite & aSpriteToRender, const CU::Vector2f & aPosition)
{
	RenderData tempRenderData(aSpriteToRender.GetColor());
	GetInstance().AddRenderCommand(RenderCommand(*aSpriteToRender.GetSprite(), aPosition, 10000.f, static_cast<USHORT>(aSpriteToRender.GetLayer()), tempRenderData));
}

void RenderConverter::AddRenderCommand(RenderCommand & aRenderCommand)
{
	GetInstance().myRenderer.AddRenderCommand(aRenderCommand);
}

void RenderConverter::DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor)
{
	GetInstance().myRenderer.DrawLine(aStartPosition, aEndPosition, aColor);
}

void RenderConverter::DrawIsometricLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition)
{
	CU::Vector2f tempOffset(550.f, 250.f);
	CU::Vector2f newStartPos = CU::IsometricToPixel(aStartPosition);
	newStartPos += tempOffset;

	CU::Vector2f newEndPos = CU::IsometricToPixel(aEndPosition);
	newEndPos += tempOffset;

	GetInstance().myRenderer.DrawLine(newStartPos, newEndPos);
}

void RenderConverter::Draw()
{
	GetInstance().myRenderer.Draw();
}

void RenderConverter::SwapBuffers()
{
	GetInstance().myRenderer.SwapBuffer();
}

void RenderConverter::RecieveMessage(const LevelTileMetricsMessage & aMessage)
{
	myLevelTileLayout = aMessage.myWidthHeight;
}