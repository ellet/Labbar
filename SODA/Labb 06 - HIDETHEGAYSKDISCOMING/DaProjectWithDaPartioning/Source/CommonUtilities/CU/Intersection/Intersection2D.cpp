#pragma once
#include "stdafx.h"
#include "Shapes2D.h"
#include "Intersection2D.h"
#include <cmath>

namespace Intersection2D
{

	bool KnownPointVsLineSegment(CU::Vector2f aPoint, const LineSegment2D & aLine)
	{
		const float LineLength = (aLine.myEndPos - aLine.myStartPos).Length2();

		const float pointLength1 = (aPoint - aLine.myStartPos).Length2();


		if (pointLength1 > LineLength)
		{
			return false;
		}

		const float pointLength2 = (aPoint - aLine.myEndPos).Length2();

		if (pointLength2 > LineLength)
		{
			return false;
		}

		return true;
	}

	bool LineVsLine(const LineSegment2D & aFirstLine, const LineSegment2D & aSecondLine, CU::Vector2f & anIntersectionPoint)
	{
		const CU::Vector2f Line1 = aFirstLine.myEndPos - aFirstLine.myStartPos;
		const CU::Vector2f Line2 = aSecondLine.myEndPos - aSecondLine.myStartPos;

		const CU::Vector2f Line1Normal = CU::Vector2f(-Line1.y, Line1.x).Normalize();

		const CU::Vector2f Line2Normal = CU::Vector2f(-Line2.y, Line2.x).Normalize();

		const float Line1DistanceFromZero = CU::Vector2f::Dot(Line1Normal, aFirstLine.myStartPos);
		const float Line2DistanceFromZero = CU::Vector2f::Dot(Line2Normal, aSecondLine.myStartPos);

		const float numeratorX = (Line2Normal.y * Line1DistanceFromZero) - (Line1Normal.y * Line2DistanceFromZero);
		const float numeratorY = (Line1Normal.x * Line2DistanceFromZero) - (Line2Normal.x * Line1DistanceFromZero);

		const float denominator = (Line1Normal.x * Line2Normal.y) - (Line2Normal.x * Line1Normal.y);

		if (denominator == 0)
		{
			if (numeratorX == 0 && numeratorY == 0)
			{
				const float Line1Length = Line1.Length();
				const float Line2Length = Line2.Length();

				const CU::Vector2f Line1Normalized = Line1.GetNormalized();
				const CU::Vector2f Line2Normalized = Line2.GetNormalized();



				if (Line1Normalized.Dot(aSecondLine.myEndPos - aFirstLine.myStartPos) < Line1Length &&
					Line1Normalized.Dot(aSecondLine.myEndPos - aFirstLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aSecondLine.myEndPos;
					return true;
				}



				if (Line1Normalized.Dot(aSecondLine.myStartPos - aFirstLine.myStartPos) < Line1Length &&
					Line1Normalized.Dot(aSecondLine.myStartPos - aFirstLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aSecondLine.myStartPos;
					return true;
				}


				if (Line1Normalized.Dot(aFirstLine.myEndPos - aSecondLine.myStartPos) < Line2Length &&
					Line1Normalized.Dot(aFirstLine.myEndPos - aSecondLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aFirstLine.myEndPos;
					return true;
				}


				if (Line1Normalized.Dot(aFirstLine.myStartPos - aSecondLine.myStartPos) < Line2Length &&
					Line1Normalized.Dot(aFirstLine.myStartPos - aSecondLine.myStartPos) > 0.f)
				{
					anIntersectionPoint = aFirstLine.myStartPos;
					return true;
				}

				return false;

			}

			return false;
		}

		CU::Vector2f tempPoint;

		tempPoint.x = numeratorX / denominator;
		tempPoint.y = numeratorY / denominator;

		if (KnownPointVsLineSegment(tempPoint, aFirstLine) == false ||
			KnownPointVsLineSegment(tempPoint, aSecondLine) == false)
		{
			return false;
		}

		anIntersectionPoint.x = tempPoint.x;
		anIntersectionPoint.y = tempPoint.y;

		return true;
	}

	bool AABBVsAABB2D(const AABB2D & aFirstCube, const AABB2D & aSecondCube)
	{
		if (aFirstCube.myMinPos.x >= aSecondCube.myMaxPos.x ||
			aFirstCube.myMaxPos.x <= aSecondCube.myMinPos.x ||
			aFirstCube.myMinPos.y >= aSecondCube.myMaxPos.y ||
			aFirstCube.myMaxPos.y <= aSecondCube.myMinPos.y)
		{
			return false;
		}
		return true;
	}

	bool AABBvsCircle(const AABB2D & aCube, const Circle2D & aCircle)
	{
		if ((aCircle.myMainPoint - aCube.GetClosestPoint(aCircle.myMainPoint)).Length() < aCircle.myRadius)
		{
			return true;
		}
		return false;
	}

	bool PointInsideAABB2D(const AABB2D & aAABB, const CU::Vector2f & aPoint)
	{
		if (aPoint.x > aAABB.myMinPos.x &&
			aPoint.x < aAABB.myMaxPos.x &&
			aPoint.y > aAABB.myMinPos.y &&
			aPoint.y < aAABB.myMaxPos.y)
		{
			return true;
		}
		return false;
	}

	bool LineVsCircle(const LineSegment2D & aLine, const Circle2D & aCircle, CU::Vector2f & anIntersectionPoint)
	{
		CU::Vector2f hypotenuse = aCircle.myMainPoint - aLine.myStartPos;

		CU::Vector2f directionOfLine = aLine.myEndPos - aLine.myStartPos;
		directionOfLine.Normalize();

		CU::Vector2f lineToMiddle = directionOfLine * ((directionOfLine.Dot(hypotenuse)));

		float toRoot = (aCircle.RadiusSquared() - hypotenuse.Length2() + lineToMiddle.Length2());
		if (toRoot < 0)
		{
			return false;
		}
		float perpendicular = (sqrt(toRoot));
		CU::Vector2f difference = lineToMiddle - (directionOfLine * perpendicular);
		anIntersectionPoint = aLine.myStartPos + directionOfLine * (directionOfLine.Dot(difference));
		if (KnownPointVsLineSegment(anIntersectionPoint, aLine) == false)
		{
			return false;
		}

		return true;
	}

	bool PointVsCircle(CU::Vector2f aPoint, const Circle2D aCircle)
	{
		if ((aPoint - aCircle.myMainPoint).Length2() < aCircle.RadiusSquared())
		{
			return true;
		}
		return false;
	}


	bool CircleVSCircle(const Circle2D & aFirstCircle, const Circle2D & aSecondCircle)
	{
		const float Distance = (aFirstCircle.myMainPoint - aSecondCircle.myMainPoint).Length();

		if ((aFirstCircle.myRadius + aSecondCircle.myRadius) > Distance)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool LineVsSweptCircle(const LineSegment2D & aLine, LineSegment2D aSweptLine, const float aSweptRadius)
	{
		if (PointVsCircle(aLine.myStartPos, Circle2D(aSweptLine.myStartPos, aSweptRadius)) == true||
			PointVsCircle(aLine.myStartPos, Circle2D(aSweptLine.myEndPos, aSweptRadius)) == true ||
			PointVsCircle(aLine.myEndPos, Circle2D(aSweptLine.myStartPos, aSweptRadius)) == true ||
			PointVsCircle(aLine.myEndPos, Circle2D(aSweptLine.myEndPos, aSweptRadius)) == true)
		{
			return true;
		}

		CU::Vector2f closestPoint;
		if (DistanceToLine2(aLine, aSweptLine.myStartPos) > DistanceToLine2(aLine, aSweptLine.myEndPos))
		{
			closestPoint = aSweptLine.myEndPos;
		}
		else
		{
			closestPoint = aSweptLine.myStartPos;
		}

		bool side = aLine.IsInside(closestPoint);
		CU::Vector2f movement;
		if (side == false)
		{
			movement = -aLine.GetNormal() * aSweptRadius;
		}
		else
		{
			movement = aLine.GetNormal() * aSweptRadius;
		}
		aSweptLine.ChangePosition(aSweptLine.myStartPos + movement, aSweptLine.myEndPos + movement);

		CU::Vector2f tempPosition = CU::Vector2f::Zero;
		return LineVsLine(aLine, aSweptLine, tempPosition);
	}


	float DistanceToLine(const LineSegment2D & aLine, const CU::Vector2f & aPositition)
	{
		CU::Vector2f d = aLine.myEndPos - aLine.myStartPos;
		d.Normalize();

		CU::Vector2f e = (aPositition - aLine.myStartPos);
		CU::Vector2f a = d * e.Dot(d);

		return sqrt(e.Length2() - a.Length2());
	}

	float DistanceToLine2(const LineSegment2D & aLine, const CU::Vector2f & aPositition)
	{
		CU::Vector2f d = aLine.myEndPos - aLine.myStartPos;
		d.Normalize();

		CU::Vector2f e = (aPositition - aLine.myStartPos);
		CU::Vector2f a = d * e.Dot(d);

		return (e.Length2() - a.Length2());
	}

	CU::Point2f ClosestPtPointTriangle(CU::Point2f p, CU::Point2f a, CU::Point2f b, CU::Point2f c)
	{
		// Check if P in vertex region outside A
		CU::Vector2f ab = b - a;
		CU::Vector2f ac = c - a;
		CU::Vector2f ap = p - a;
		float d1 = ab.Dot(ap);
		float d2 = ac.Dot(ap);
		if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)
												// Check if P in vertex region outside B
		CU::Vector2f bp = p - b;
		float d3 = ab.Dot(bp);
		float d4 = ac.Dot(bp);
		if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)
											  // Check if P in edge region of AB, if so return projection of P onto AB
		float vc = d1*d4 - d3*d2;
		if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
			float v = d1 / (d1 - d3);
			return a + ab * v; // barycentric coordinates (1-v,v,0)
		}
		// Check if P in vertex region outside C
		CU::Vector2f cp = p - c;
		float d5 = ab.Dot(cp);
		float d6 = ac.Dot(cp);
		if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)
			// Check if P in edge region of AC, if so return projection of P onto AC
			float vb = d5*d2 - d1*d6;
		if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
			float w = d2 / (d2 - d6);
			return a + ac * w; // barycentric coordinates (1-w,0,w)
		}
		// Check if P in edge region of BC, if so return projection of P onto BC
		float va = d3*d6 - d5*d4;
		if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
			float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
			return b + (c - b) * w; // barycentric coordinates (0,1-w,w)
		}
		// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
		float denom = 1.0f / (va + vb + vc);
		float v = vb * denom;
		float w = vc * denom;
		return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f-v-w
	}

	bool TriangleVSCircle(const Triangle & aTriangle, const Circle2D & aCircle)
	{
		CU::Point2f closestPoint = ClosestPtPointTriangle(aCircle.myMainPoint, aTriangle.myFirstLine.myStartPos, aTriangle.mySecondLine.myStartPos, aTriangle.myThirdLine.myStartPos);

		return PointVsCircle(closestPoint, aCircle);
		//	CU::Vector2f firstBoundary = aTriangle.myFirstLine.GetNormal();
		//	float firstPoint = aTriangle.myFirstLine.GetNormal().Dot(aCircle.myMainPoint + (firstBoundary * aCircle.myRadius));

		///*	if (firstPoint > 0)
		//	{
		//		return true;
		//	}*/

		//	CU::Vector2f secondBoundary = aTriangle.mySecondLine.GetNormal();
		//	float secondPoint = aTriangle.mySecondLine.GetNormal().Dot(aCircle.myMainPoint + (secondBoundary * aCircle.myRadius));

		//	/*if (secondPoint > 0)
		//	{
		//		return true;
		//	}*/

		//	CU::Vector2f thirdBoundary = aTriangle.myThirdLine.GetNormal();
		//	float thirdPoint = aTriangle.myThirdLine.GetNormal().Dot(aCircle.myMainPoint + (thirdBoundary * aCircle.myRadius));

		//	if (thirdPoint > 0)
		//	{
		//		return true;
		//	}

		//	return false;
	}

}