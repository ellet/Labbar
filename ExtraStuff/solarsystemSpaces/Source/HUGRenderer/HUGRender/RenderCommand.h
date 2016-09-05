#pragma once
#include "HUGRender/SpriteData.h"


namespace DX2D
{
	class CSprite;
}

namespace HUG
{
	class RenderCommand
	{
	public:
		RenderCommand();
		RenderCommand(DX2D::CSprite * aSprite, const SpriteData & aSpriteData, const CU::Vector2f & aPosition);
		~RenderCommand();

		void Render();

	private:
		DX2D::CSprite * mySprite;
		CU::Vector2f myPosition;
		SpriteData mySpriteData;
	};

}