#pragma once
#include "HUGRender/SpriteData.h"


namespace Tga2D
{
	class CSprite;
}

namespace HUG
{
	class RenderCommand
	{
	public:
		RenderCommand();
		RenderCommand(Tga2D::CSprite * aSprite, const SpriteData & aSpriteData, const CU::Vector2f & aPosition);
		~RenderCommand();

		void Render();

	private:
		Tga2D::CSprite * mySprite;
		CU::Vector2f myPosition;
		SpriteData mySpriteData;
	};

}