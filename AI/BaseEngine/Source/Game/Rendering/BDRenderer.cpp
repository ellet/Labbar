#include "stdafx.h"
#include "BDRenderer.h"
#include "BDSprite.h"
#include "tga2d\sprite\sprite.h"

#include "tga2d\engine.h"


BDRenderer * BDRenderer::ourInstance = nullptr;

void BDRenderer::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new BDRenderer();
	}
}

void BDRenderer::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void BDRenderer::AddSprite(BDSprite & aSpriteToRender)
{
	if (GetInstance().mySprites.find(aSpriteToRender.myFilePath) == GetInstance().mySprites.end())
	{
		GetInstance().mySprites[aSpriteToRender.myFilePath] = new DX2D::CSprite(aSpriteToRender.myFilePath.c_str());
	}
}

void BDRenderer::RenderSprite(const BDSprite & aSpriteToRender)
{
	if (GetInstance().mySprites.find(aSpriteToRender.myFilePath) != GetInstance().mySprites.end())
	{
		DX2D::CSprite & sprite = *GetInstance().mySprites[aSpriteToRender.myFilePath];

		SB::Vector2f windowSize = To(DX2D::CEngine::GetInstance()->GetWindowSize());

		SB::Vector2f normPosition = aSpriteToRender.myPosition / windowSize;

		sprite.SetPosition(To(normPosition));
		sprite.Render();
	}
}



BDRenderer::BDRenderer()
{
}


BDRenderer::~BDRenderer()
{
}
