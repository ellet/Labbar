#include "stdafx.h"
#include "RenderCommand.h"


RenderCommand::RenderCommand(DX2D::CSprite aSpriteToRender)
{
	mySpriteToRender = aSpriteToRender;
}


RenderCommand::~RenderCommand()
{
}


void RenderCommand::RenderSprite()
{
	mySpriteToRender.Render();
}