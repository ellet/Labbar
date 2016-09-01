#include "stdafx.h"
#include "Renderer.h"

#include "Rend/RenderCommand.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include <tga2d/drawers/debug_drawer.h>

#include "Rend/StaticSprite.h"
#include "Rend/RenderLayerEnum.h"
#include "Rend/RenderCommand.h"


Renderer::Renderer()
{
	myCommandsToRender = new CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<RenderCommand>>();
	myBuffer = new CommonUtilities::GrowingArray<CommonUtilities::GrowingArray<RenderCommand>>();

	myCommandsToRender->Init(static_cast<USHORT>(enumRenderLayer::enumLength));
	myBuffer->Init(static_cast<USHORT>(enumRenderLayer::enumLength));

	for (USHORT iLayer = 0; iLayer < static_cast<USHORT>(enumRenderLayer::enumLength); ++iLayer)
	{
		myCommandsToRender->Add(CommonUtilities::GrowingArray<RenderCommand>());
		myCommandsToRender->GetLast().Init(128);

		myBuffer->Add(CommonUtilities::GrowingArray<RenderCommand>());
		myBuffer->GetLast().Init(128);
	}
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
	if (StaticSprite::ourSprites.IsInitialized() == false)
	{
		StaticSprite::ourSprites.Init(128);
	}
}

void Renderer::Draw() const
{
	RenderAllSprites();
}


void Renderer::AddRenderCommand(RenderCommand & aRenderCommand)
{
	aRenderCommand.myPosition.x /= static_cast<float>(myWindowSize.x);
	aRenderCommand.myPosition.y /= static_cast<float>(myWindowSize.y);
	
	for (USHORT iRenderCommand = 0; iRenderCommand < (*myBuffer)[aRenderCommand.GetLayer()].Size(); ++iRenderCommand)
	{
		if (aRenderCommand.GetPriority() < 
			(*myBuffer)[aRenderCommand.GetLayer()][iRenderCommand].GetPriority())
		{
			(*myBuffer)[aRenderCommand.GetLayer()].Insert(iRenderCommand, aRenderCommand);
			return;
		}
	}
	(*myBuffer)[aRenderCommand.GetLayer()].Add(aRenderCommand);
}

void Renderer::DrawLine(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition, const CU::Vector4f & aColor)
{
	DX2D::Vector2f tempStartPosition(aStartPosition.x / myWindowSize.x, aStartPosition.y / myWindowSize.y);
	DX2D::Vector2f tempEndPosition(aEndPosition.x / myWindowSize.x, aEndPosition.y / myWindowSize.y);
	DX2D::Vector4f color(aColor.r, aColor.g, aColor.b, aColor.a);

	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(tempStartPosition , tempEndPosition, color);
}

void Renderer::SwapBuffer()
{
	myCommandsToRender->CallFunctionOnAllMembers(std::mem_fn(&CU::GrowingArray<RenderCommand>::RemoveAll));
	std::swap(myCommandsToRender, myBuffer);
}

void Renderer::RenderAllSprites() const
{
	for (USHORT iLayer = 0; iLayer < myCommandsToRender->Size(); ++iLayer)
	{
		//(*myCommandsToRender)[iLayer].CallFunctionOnAllMembers(std::mem_fn(&RenderCommand::Render));
		for (USHORT iRenderCommand = 0; iRenderCommand < (*myBuffer)[iLayer].Size(); ++iRenderCommand)
		{
			(*myBuffer)[iLayer][iRenderCommand].Render(CU::Vector2f(static_cast<float>(myWindowSize.x), static_cast<float>(myWindowSize.y)));
		}
	}
}