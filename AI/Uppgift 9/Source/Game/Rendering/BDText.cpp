#include "stdafx.h"
#include "BDText.h"
#include "BDTextRenderer.h"


BDText::BDText()
{
}


BDText::~BDText()
{
}

void BDText::Render() const
{
	BDTextRenderer::RenderText(*this);
}


void BDText::Render(const std::string & aText) const
{
	BDText printText = *this;
	printText.myText = aText;

	BDTextRenderer::RenderText(printText);
}

void BDText::SetScale(const float aScale)
{
	myScale = aScale;
}

void BDText::SetText(const std::string & aString)
{
	myText = aString;
}

void BDText::SetPosition(const SB::Vector2f & aPosition)
{
	myPosition = aPosition;
}
