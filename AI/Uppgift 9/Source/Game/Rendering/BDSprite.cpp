#include "stdafx.h"
#include "BDSprite.h"
#include "BDRenderer.h"


BDSprite::BDSprite()
{
	myFilePath = "";
	myPosition = SB::Vector2f::Zero;
	myColor = SB::Color::White;

	myOrigin = { 0.5f, 0.5f };
	mySpriteIndex = 0;
}


BDSprite::~BDSprite()
{
}

void BDSprite::Init(const std::string & aFilePath)
{
	if (myFilePath == "")
	{
		myFilePath = aFilePath;
		BDRenderer::AddSprite(*this);
	}
	else
	{
		BDRenderer::ChangeBatch(aFilePath, *this);
	}
}


void BDSprite::Render() const
{
	BDRenderer::RenderSprite(*this);
}

void BDSprite::SetColor(const SB::Color & aColor)
{
	myColor = aColor;
}

void BDSprite::SetPosition(const SB::Vector2f & aPosition)
{
	myPosition = aPosition;
}

const SB::Vector2f & BDSprite::GetPosition() const
{
	return myPosition;
}
