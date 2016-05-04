#pragma once
#include <tga2d/sprite/sprite.h>

class RenderCommand
{
public:
	RenderCommand(DX2D::CSprite aSpriteToRender);
	~RenderCommand();

	void RenderSprite();

private:
	DX2D::CSprite mySpriteToRender;
};

