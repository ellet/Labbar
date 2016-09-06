#include "stdafx.h"
#include "Renderer.h"
#include "RenderConversions.h"


namespace HUG
{
	Renderer::Renderer()
	{
		myToRender = new CU::GrowingArray<RenderCommand>();
		myBuffer = new CU::GrowingArray<RenderCommand>();
		myToRender->Init(2048);
		myBuffer->Init(2048);
		myTextureManager.Init();
	}

	Renderer::~Renderer()
	{
		delete myToRender;
		myToRender = nullptr;
		delete myBuffer;
		myBuffer = nullptr;
	}

	void Renderer::SetTargetResolution(const CU::Vector2f & aTargetResolution)
	{
		myTargetResolution = aTargetResolution;
	}

	unsigned short Renderer::CreateSprite(const std::string & aFilePath)
	{
		return myTextureManager.AddTexture(aFilePath);
	}

	void Renderer::AddSpriteToRender(const unsigned short aSpriteIndex, const SpriteData & aSpriteData, const CU::Vector2f & aPosition)
	{
		myBuffer->Add(RenderCommand(myTextureManager.GetTexture(aSpriteIndex), aSpriteData, PixelToNormalized(aPosition, myTargetResolution)));
	}

	void Renderer::Draw()
	{
		for (unsigned short iSprite = 0; iSprite < myToRender->Size(); ++iSprite)
		{
			(*myToRender)[iSprite].Render();
		}
	}

	void Renderer::SwitchBuffers()
	{
		myToRender->RemoveAll();
		std::swap(myToRender, myBuffer);
	}

	void Renderer::DrawLine(const PixelPositionFloat & aStartPoint, const PixelPositionFloat & aEndPoint)
	{
		NormalizedPosition tempStart = PixelToNormalized(aStartPoint, myTargetResolution);
		NormalizedPosition tempEnd = PixelToNormalized(aEndPoint, myTargetResolution);
		const Tga2D::Vector2f Start(tempStart.x, tempStart.y);
		const Tga2D::Vector2f End(tempEnd.x, tempEnd.y);

		Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Start, End);
	}
}