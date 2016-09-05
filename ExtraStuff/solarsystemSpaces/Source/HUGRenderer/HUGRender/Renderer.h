#pragma once
#include <CU/MainSingleton/BaseSingletons/BaseRenderer.h>
#include "HugRender/RenderCommand.h"
#include "HUGRender/TextureManager.h"

namespace HUG
{
	class Renderer : public CU::BaseRenderer
	{
	public:
		Renderer();
		~Renderer();

		void SetTargetResolution(const PixelPositionFloat & aTargetResolution);

		unsigned short CreateSprite(const std::string & aFilePath);

		void AddSpriteToRender(const unsigned short aSpriteIndex, const SpriteData & aSpriteData, const CU::Vector2f & aPosition);

		void Draw();

		void DrawLine(const PixelPositionFloat & aStartPoint, const PixelPositionFloat & aEndPoint);

		void SwitchBuffers();

	private:
		TextureManager myTextureManager;
		CU::GrowingArray<RenderCommand> * myToRender;
		CU::GrowingArray<RenderCommand> * myBuffer;

		CU::Vector2f myTargetResolution;
	};
}


#define GET_RENDERER CU::MainSingleton::GetRenderer<HUG::Renderer>() 