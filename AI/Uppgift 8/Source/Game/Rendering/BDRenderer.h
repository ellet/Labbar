#pragma once
#include <unordered_map>

class BDSprite;

namespace Tga2D
{
	class CSprite;
}

class BDRenderer
{
public:
	static void Create();
	static void Destroy();

	static void AddSprite(BDSprite & aSpriteToRender);
	static void RenderSprite(const BDSprite & aSpriteToRender);

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

	std::unordered_map<std::string, Tga2D::CSprite*> mySprites;

	BDRenderer();
	~BDRenderer();
};

