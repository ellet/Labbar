#include "stdafx.h"

#include "text/text.h"
#include "engine.h"
#include "text/text_service.h"

using namespace Tga2D;

CText::CText(const char* aPathAndName, EFontSize aFontSize, unsigned char aBorderSize)
: myTextService(&Tga2D::CEngine::GetInstance()->GetTextService())
{
	myColor.Set(1, 0, 1, 1);
	myScale = 1.0f;
	myPathAndName = aPathAndName;
	Tga2D::CEngine::GetInstance()->GetTextService().InitAndLoad(myPathAndName, aBorderSize, aFontSize);
	myRenderName = Tga2D::CEngine::GetInstance()->GetTextService().GetRenderName(myPathAndName, aFontSize);
	mySampler = ESamplerType_Point;
}


CText::~CText()
{
}

void Tga2D::CText::Render()
{
	if (!myTextService)
	{
		return;
	}
	if (!myTextService->AddTextToRender(myText, myPosition, myColor, myScale, myRenderName, mySampler))
	{
		ERROR_PRINT("%s", "Text rendering error! Trying to render a text where the resource has been deleted! Did you clear the memory for this font?");
	}
}

float Tga2D::CText::GetWidth()
{
	if (!myTextService)
	{
		return 0.0f;
	}

	return myTextService->GetSentenceWidth(this) / CEngine::GetInstance()->GetWindowSize().x;
}
