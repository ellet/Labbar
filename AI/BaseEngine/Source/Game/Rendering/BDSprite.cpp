#include "stdafx.h"
#include "BDSprite.h"
#include "BDRenderer.h"


BDSprite::BDSprite()
{
	myFilePath = "";
	myPosition = SB::Vector2f::Zero;
}


BDSprite::~BDSprite()
{
}

void BDSprite::Init(const std::string & aFilePath)
{
	myFilePath = aFilePath;
	BDRenderer::AddSprite(*this);
}


void BDSprite::Render()
{
	BDRenderer::RenderSprite(*this);
}

void BDSprite::SetPosition(const SB::Vector2f & aPosition)
{
	myPosition = aPosition;
}
