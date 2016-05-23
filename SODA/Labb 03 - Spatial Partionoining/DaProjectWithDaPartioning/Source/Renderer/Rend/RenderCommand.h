#pragma once
#include "Rend/RenderData.h"

namespace DX2D
{
	class CSprite;
}

class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(DX2D::CSprite & aSpriteToRender, const CU::Vector2f & aPosition, const float aPriority, const USHORT aLayer, const RenderData & aRenderData);
	~RenderCommand();

	void Render() const;
	float GetPriority()
	{
		return myRenderPriority;
	}

	USHORT GetLayer()
	{
		return myLayer;
	}
	
	CU::Vector2f myPosition;

private:
	USHORT myLayer;
	RenderData myRenderData;
	float myRenderPriority;
	DX2D::CSprite * mySprite;
};
