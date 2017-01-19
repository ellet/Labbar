#pragma once
#include <unordered_map>
#include "Utilities\Container\GrowingArray.h"

class BDSprite;

namespace Tga2D
{
	class CSprite;
	class CSpriteBatch;
}

class BDRenderer
{
public:
	static void Create();
	static void Destroy();

	static void AddSprite(BDSprite & aSpriteToRender);
	static void RenderSprite(const BDSprite & aSpriteToRender);

	static void Render();

private:
	static BDRenderer & GetInstance()
	{
		if (ourInstance == nullptr)
		{
			Error("Rendere is nullptr");
		}

		return *ourInstance;
	}

	static BDRenderer * ourInstance;

	std::unordered_map<std::string, Tga2D::CSpriteBatch*> mySpritesBatches;
	SB::GrowingArray<Tga2D::CSprite*> mySpritesData;

	BDRenderer();
	~BDRenderer();
};

