#include "stdafx.h"

#include "sprite/textured_quad.h"
#include "d3d/direct_3d.h"
#include "DDSTextureLoader.h"
#include "engine.h"
#include "render/renderer.h"
#include "texture/texture_manager.h"
#include <d3d11.h>

using namespace Tga2D;

CTexturedQuad::CTexturedQuad(void)
		:myTexture(nullptr)
		, myCustomShader(nullptr)
{
	myEngine = CEngine::GetInstance();

	myTextureRect.myStartX = 0.0f;
	myTextureRect.myStartY = 0.0f;
	myTextureRect.myEndX = 1.0f;
	myTextureRect.myEndY = 1.0f;
	for (int i = 0; i < MAP_MAX; i++)
	{
		myMaps[i] = NULL;
	}
}


CTexturedQuad::~CTexturedQuad(void)
{
}

void Tga2D::CTexturedQuad::Init(const char* aTexturePath)
{
	if (aTexturePath)
	{
		myTexture = myEngine->GetTextureManager().GetTexture(aTexturePath);
		mySize = myTexture->mySize;
		myImageSize = myTexture->myImageSize;
	}
	else
	{
		myTexture = myEngine->GetTextureManager().GetWhiteSquareTexture();
	}
}

void Tga2D::CTexturedQuad::Render()
{
	myEngine->GetRenderer().AddToRender(this);
}

void Tga2D::CTexturedQuad::SetTextureRect(float aStartX, float aStartY, float aEndX, float aEndY)
{
	myTextureRect.myStartX = aStartX;
	myTextureRect.myStartY = aStartY;
	myTextureRect.myEndX = aEndX;
	myTextureRect.myEndY = aEndY;
}

void CTexturedQuad::SetColor(CColor aColor)
{
	myColor = aColor;
}

const CColor& Tga2D::CTexturedQuad::GetColor() const
{
	return myColor;
}

const Tga2D::CColor& Tga2D::CTexturedQuad::GetColor()
{
	return myColor;
}

void Tga2D::CTexturedQuad::SetSize(const Vector2f& aSize)
{
	mySize = aSize;
}

void Tga2D::CTexturedQuad::SetUV(const Vector2f& aUV)
{
	myUV = aUV;
}

void Tga2D::CTexturedQuad::SetMap(EShaderMap aMapType, const char* aPath)
{
	myMaps[aMapType] = myEngine->GetTextureManager().GetTexture(aPath);
}
