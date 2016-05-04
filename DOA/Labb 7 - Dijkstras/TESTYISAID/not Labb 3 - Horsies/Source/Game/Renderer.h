#pragma once

#include <GrowingArray/GrowingArray.h>
#include <Vectors/Vector2.h>
#include <Vectors/vector4.h>

struct LineData
{
	LineData() :
		myStartPosition(Vector2f::Zero), myEndPosition(Vector2f::Zero), myColor(Vector4f::One)
	{
	}

	LineData(const Vector2f & aStartPosition, const Vector2f & aEndPosition) :
		myStartPosition(aStartPosition), myEndPosition(aEndPosition), myColor(Vector4f::One)
	{}

	LineData(const Vector2f & aStartPosition, const Vector2f & aEndPosition, const Vector4f & aColor) :
		myStartPosition(aStartPosition), myEndPosition(aEndPosition), myColor(aColor)
	{}

	Vector2f myStartPosition;
	Vector2f myEndPosition;
	Vector4f myColor;
};

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
}

class WrappedSprite;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();

	void AddNodeToDraw(WrappedSprite & aSpriteToAdd);
	void AddLinkToDraw(const LineData & aLinkToDraw);
	
	void Draw();

	void SetWindowSize(const Vector2ui aWindowSize);

	void ResetRender();

private:
	
	Vector2ui myWindowSize;

	void RenderLines();
	void RenderLine(const LineData & aLineToDraw);

	DX2D::CSpriteBatch * myNodesToDraw;
	
	CU::GrowingArray<DX2D::CSprite*> mySpritesToDraw;
	CU::GrowingArray<LineData> myLinksToDraw;
};



inline void Renderer::SetWindowSize(const Vector2ui aWindowSize)
{
	myWindowSize = aWindowSize;
}