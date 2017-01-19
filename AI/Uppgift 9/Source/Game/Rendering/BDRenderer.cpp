#include "stdafx.h"
#include "BDRenderer.h"
#include "BDSprite.h"
#include "tga2d\sprite\sprite.h"

#include "tga2d\engine.h"
#include "tga2d\sprite\sprite_batch.h"




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

void BDRenderer::ChangeBatch(const std::string & ChangeBatch, BDSprite & aSpriteToRender)
{
	Tga2D::CSprite & currentSprite = * GetInstance().mySpritesData[aSpriteToRender.mySpriteIndex];
	Tga2D::CSpriteBatch & currentBatch = *GetInstance().mySpritesBatches[aSpriteToRender.myFilePath];

	currentBatch.RemoveObject(&currentSprite);

	aSpriteToRender.myFilePath = ChangeBatch;
	GetInstance().AddToBatch(aSpriteToRender, currentSprite);
}

void BDRenderer::AddSprite(BDSprite & aSpriteToRender)
{
	Tga2D::CSprite * newSprite = new Tga2D::CSprite();
	GetInstance().AddToBatch(aSpriteToRender, *newSprite);

	GetInstance().mySpritesData.Add(newSprite);

	aSpriteToRender.mySpriteIndex = GetInstance().mySpritesData.Size() - 1;
}

void BDRenderer::AddToBatch(BDSprite & aSpriteToRender, Tga2D::CSprite & aSprite)
{
	if (GetInstance().mySpritesBatches.find(aSpriteToRender.myFilePath) == GetInstance().mySpritesBatches.end())
	{
		GetInstance().mySpritesBatches[aSpriteToRender.myFilePath] = new Tga2D::CSpriteBatch(true);
		GetInstance().mySpritesBatches[aSpriteToRender.myFilePath]->Init(aSpriteToRender.myFilePath.c_str());
	}

	aSprite.SetShouldRender(false);
	Tga2D::CSpriteBatch & currentBatch = *GetInstance().mySpritesBatches[aSpriteToRender.myFilePath];
	currentBatch.AddObject(&aSprite);
}

void BDRenderer::RenderSprite(const BDSprite & aSpriteToRender)
{
	if (GetInstance().mySpritesBatches.find(aSpriteToRender.myFilePath) != GetInstance().mySpritesBatches.end())
	{
		Tga2D::CSprite & sprite = *GetInstance().mySpritesData[aSpriteToRender.mySpriteIndex];

		SB::Vector2f windowSize = To(Tga2D::CEngine::GetInstance()->GetWindowSize());

		SB::Vector2f normPosition = aSpriteToRender.myPosition / windowSize;

		sprite.SetPivot(To(aSpriteToRender.myOrigin));
		sprite.SetPosition(To(normPosition));
		sprite.SetShouldRender(true);
	}
}

void BDRenderer::Render()
{
	for (std::unordered_map<std::string, Tga2D::CSpriteBatch*>::iterator iBatch = GetInstance().mySpritesBatches.begin(); iBatch != GetInstance().mySpritesBatches.end(); ++iBatch)
	{
		iBatch->second->Render();
	}

	for (unsigned short iSprite = 0; iSprite < GetInstance().mySpritesData.Size(); ++iSprite)
	{
		GetInstance().mySpritesData[iSprite]->SetShouldRender(false);
	}
}

BDRenderer::BDRenderer()
{
}


BDRenderer::~BDRenderer()
{
}
