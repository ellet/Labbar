#pragma once
#include "Shapes2D.h"
#include <cmath>

namespace Intersection2D
{

	bool KnownPointVsLineSegment(Vector2f aPoint, const LineSegment2D & aLine);
	
	bool LineVsLine(const LineSegment2D & aFirstLine, const LineSegment2D & aSecondLine, Vector2f & anIntersectionPoint);
	
	bool AABBVsAABB2D(const AABB2D & aFirstCube, const AABB2D & aSecondCube);
	
	bool PointInsideAABB2D(const AABB2D & aAABB, const Vector2f & aPoint);

	bool LineVsCircle(const LineSegment2D & aLine, const Circle2D & aCircle, Vector2f & anIntersectionPoint);

	bool PointVsCircle(Vector2f aPoint, const Circle2D aCircle);

	bool LineVsSweptCircle(const LineSegment2D & aLine, LineSegment2D aSweptLine, const float aSweptRadius);

	float DistanceToLine(const LineSegment2D & aLine, const Vector2f & aPositition);

	float DistanceToLine2(const LineSegment2D & aLine, const Vector2f & aPositition);
}