#pragma once

namespace HUG
{
	void DrawShape(const Intersection2D::AABB2D & aSquare);
	void DrawShape(const Intersection2D::Circle2D & aCircle, const unsigned short aCornerAmount = 8);

	void DrawBoxWithLines(const Intersection2D::AABB2D & aSquare);
	void DrawCircleWithLines(const Intersection2D::Circle2D & aCircle, const unsigned short aCornerAmount = 8);
}