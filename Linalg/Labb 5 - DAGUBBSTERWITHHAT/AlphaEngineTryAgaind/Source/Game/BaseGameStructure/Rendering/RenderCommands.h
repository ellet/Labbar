#pragma once
#include "../CommonUtilities/Vectors/vector2.h"
#include "WorldSpace.h"

namespace DX2D
{
	class CSprite;
}

class WorldSpace;

class RenderCommands
{
public:
	RenderCommands();
	~RenderCommands();

	void Init(DX2D::CSprite * const aSprite, Vector2<float> aPosition, WorldSpace * aWorldSpace);

	void Render();

private:
	
	DX2D::CSprite * mySprite;
	Vector2<float> myPosition;

	WorldSpace * myLocalSpace;
};

