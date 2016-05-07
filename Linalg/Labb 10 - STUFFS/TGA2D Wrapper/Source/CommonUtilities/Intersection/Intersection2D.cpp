#pragma once
#include "Shapes2D.h"
#include "Intersection2D.h"
#include <cmath>

namespace Intersection2D
{

	bool KnownPointVsLineSegment(Vector2f aPoint, const LineSegment2D & aLine)
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

	bool LineVsLine(const LineSegment2D & aFirstLine, const LineSegment2D & aSecondLine, Vector2f & anIntersectionPoint)
	{
		const Vector2f Line1 = aFirstLine.myEndPos - aFirstLine.myStartPos;
		const Vector2f Line2 = aSecondLine.myEndPos - aSecondLine.myStartPos;

		const Vector2f Line1Normal = Vector2f(-Line1.y, Line1.x).Normalize();

		const Vector2f Line2Normal = Vector2f(-Line2.y, Line2.x).Normalize();

		const float Line1DistanceFromZero = Vector2f::Dot(Line1Normal, aFirstLine.myStartPos);
		const float Line2DistanceFromZero = Vector2f::Dot(Line2Normal, aSecondLine.myStartPos);

		const float numeratorX = (Line2Normal.y * Line1DistanceFromZero) - (Line1Normal.y * Line2DistanceFromZero);
		const float numeratorY = (Line1Normal.x * Line2DistanceFromZero) - (Line2Normal.x * Line1DistanceFromZero);

		const float denominator = (Line1Normal.x * Line2Normal.y) - (Line2Normal.x * Line1Normal.y);

		if (denominator == 0)
		{
			if (numeratorX == 0 && numeratorY == 0)
			{
				const float Line1Length = Line1.Length();
				const float Line2Length = Line2.Length();

				const Vector2f Line1Normalized = Line1.GetNormalized();
				const Vector2f Line2Normalized = Line2.GetNormalized();



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

		Vector2f tempPoint;

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

	bool PointInsideAABB2D(const AABB2D & aAABB, const Vector2f & aPoint)
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

	bool LineVsCircle(const LineSegment2D & aLine, const Circle2D & aCircle, Vector2f & anIntersectionPoint)
	{
		Vector2f hypotenuse = aCircle.myMainPoint - aLine.myStartPos;

		Vector2f directionOfLine = aLine.myEndPos - aLine.myStartPos;
		directionOfLine.Normalize();

		Vector2f lineToMiddle = directionOfLine * ((directionOfLine.Dot(hypotenuse)));

		float toRoot = (aCircle.RadiusSquared() - hypotenuse.Length2() + lineToMiddle.Length2());
		if (toRoot < 0)
		{
			return false;
		}
		float perpendicular = (sqrt(toRoot));
		Vector2f difference = lineToMiddle - (directionOfLine * perpendicular);
		anIntersectionPoint = aLine.myStartPos + directionOfLine * (directionOfLine.Dot(difference));
		if (KnownPointVsLineSegment(anIntersectionPoint, aLine) == false)
		{
			return false;
		}

		return true;
	}

	bool PointVsCircle(Vector2f aPoint, const Circle2D aCircle)
	{
		if ((aPoint - aCircle.myMainPoint).Length2() < aCircle.RadiusSquared())
		{
			return true;
		}
		return false;
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

		Vector2f closestPoint;
		if (DistanceToLine2(aLine, aSweptLine.myStartPos) > DistanceToLine2(aLine, aSweptLine.myEndPos))
		{
			closestPoint = aSweptLine.myEndPos;
		}
		else
		{
			closestPoint = aSweptLine.myStartPos;
		}

		bool side = aLine.IsInside(closestPoint);
		Vector2f movement;
		if (side == false)
		{
			movement = -aLine.GetNormal() * aSweptRadius;
		}
		else
		{
			movement = aLine.GetNormal() * aSweptRadius;
		}
		aSweptLine.ChangePosition(aSweptLine.myStartPos + movement, aSweptLine.myEndPos + movement);

		return LineVsLine(aLine, aSweptLine, Vector2f(0.f, 0.f));
	}


	float DistanceToLine(const LineSegment2D & aLine, const Vector2f & aPositition)
	{
		Vector2f d = aLine.myEndPos - aLine.myStartPos;
		d.Normalize();

		Vector2f e = (aPositition - aLine.myStartPos);
		Vector2f a = d * e.Dot(d);

		return sqrt(e.Length2() - a.Length2());
	}

	float DistanceToLine2(const LineSegment2D & aLine, const Vector2f & aPositition)
	{
		Vector2f d = aLine.myEndPos - aLine.myStartPos;
		d.Normalize();

		Vector2f e = (aPositition - aLine.myStartPos);
		Vector2f a = d * e.Dot(d);

		return (e.Length2() - a.Length2());
	}
}