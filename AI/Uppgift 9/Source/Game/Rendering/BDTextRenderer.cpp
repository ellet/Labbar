#include "stdafx.h"
#include "BDTextRenderer.h"
#include "BDText.h"
#include "tga2d\text\text.h"

BDTextRenderer * BDTextRenderer::ourInstance = nullptr;

void BDTextRenderer::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new BDTextRenderer();
	}
}

void BDTextRenderer::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void BDTextRenderer::Init()
{
	GetInstance().myText = new Tga2D::CText("Text/arial.ttf");
}

void BDTextRenderer::RenderText(const BDText & aTextToRender)
{
	GetInstance().myTextToRender.Add(aTextToRender);
}

void BDTextRenderer::Render()
{
	const SB::Vector2f WindowSize = To(Tga2D::CEngine::GetInstance()->GetWindowSize());

	for (unsigned short iText = 0; iText < GetInstance().myTextToRender.Size(); ++iText)
	{
		const BDText & currentText = GetInstance().myTextToRender[iText];

		SB::Vector2f normPosition = currentText.myPosition / WindowSize;

		GetInstance().myText->myScale = currentText.myScale;
		GetInstance().myText->myPosition = To(normPosition);
		GetInstance().myText->myText = currentText.myText;
		GetInstance().myText->Render();
	}

	GetInstance().myTextToRender.RemoveAll();
}



BDTextRenderer::BDTextRenderer()
{
	myText = nullptr;
}


BDTextRenderer::~BDTextRenderer()
{
}
