#pragma once

#include <GrowingArray/GrowingArray.h>
//#include <Vectors/Vector2.h>

//struct LineData
//{
//	LineData();
//	LineData(const Vector2f & aStartPosition, const Vector2f & aEndPosition) :
//		myStartPosition(aStartPosition), myEndPosition(aEndPosition)
//	{}
//
//	Vector2f myStartPosition;
//	Vector2f myEndPosition;
//};

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
}

class Renderer
{
public:
	Renderer();
	~Renderer();

	//void AddNodeToDraw(DX2D::CSprite & aSpriteToAdd);
	////void AddLinkToDraw(const LineData & aLinkToDraw);

	//void Draw();

private:
	//void RenderLines();
	////void RenderLine(const LineData & aLineToDraw);

	//DX2D::CSpriteBatch * myNodesToDraw;
	//CommonUtilities::GrowingArray<LineData> myLinksToDraw;
};