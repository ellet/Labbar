#include "stdafx.h"
#include "DrawShapes.h"

namespace HUG
{
	void DrawShape(const Intersection2D::AABB2D & aSquare)
	{
		DrawBoxWithLines(aSquare);
	}

	void DrawShape(const Intersection2D::Circle2D & aCircle, const unsigned short aCornerAmount /*= 8*/)
	{
		DrawCircleWithLines(aCircle);
	}

	void DrawBoxWithLines(const Intersection2D::AABB2D & aSquare)
	{
		PixelPositionFloat BottomLeft = aSquare.myMinPos;
		PixelPositionFloat TopRight = aSquare.myMaxPos;
		PixelPositionFloat BottomRight(TopRight.x, BottomLeft.y);
		PixelPositionFloat TopLeft(BottomLeft.x, TopRight.y);

		GET_RENDERER.DrawLine(BottomLeft, TopLeft);
		GET_RENDERER.DrawLine(TopLeft, TopRight);
		GET_RENDERER.DrawLine(TopRight, BottomRight);
		GET_RENDERER.DrawLine(BottomRight, BottomLeft);
	}

	void DrawCircleWithLines(const Intersection2D::Circle2D & aCircle, const unsigned short aCornerAmount /*= 8*/)
	{
		unsigned short cornerAmount = aCornerAmount;
		if (cornerAmount < 4)
		{
			cornerAmount = 4;
		}

		const float CornerOffset = DEGRESS_TO_RADIANSF(360.f) / FLOATCAST(cornerAmount);
		PixelPositionFloat radiusVector(aCircle.myRadius, 0.f);
		PixelPositionFloat startPoint = aCircle.myMainPoint + radiusVector;
		PixelPositionFloat endPoint;

		for (unsigned short iLine = 1; iLine < cornerAmount + 1; ++iLine)
		{
			endPoint = aCircle.myMainPoint + (radiusVector * CU::Matrix33f::CreateRotateAroundZ(CornerOffset * iLine));
			GET_RENDERER.DrawLine(startPoint, endPoint);
			startPoint = endPoint;
		}
	}

}