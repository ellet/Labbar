#include "stdafx.h"
#include "TextureManager.h"
#include <tga2d/sprite/sprite.h>

namespace HUG
{

	TextureManager::TextureManager()
	{
	}


	TextureManager::~TextureManager()
	{
		mySprites.DeleteAll();
	}

	void TextureManager::Init(const unsigned short aInitNumber /*= 1024*/)
	{
		mySprites.Init(aInitNumber);
	}

	unsigned short TextureManager::AddTexture(const std::string & aFilePath)
	{
		mySprites.Add(new Tga2D::CSprite(aFilePath.c_str()));
		return mySprites.Size() - 1;
	}

	Tga2D::CSprite * TextureManager::GetTexture(const unsigned short anIndex)
	{
		return mySprites[anIndex];
	}

}