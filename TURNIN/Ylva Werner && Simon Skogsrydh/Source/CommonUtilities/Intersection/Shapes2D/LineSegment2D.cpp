#include "LineSegment2D.h"

namespace Intersection2D
{


	LineSegment2D::LineSegment2D()
	{
	}


	void LineSegment2D::ChangePosition(const Vector2f aPosition)
	{
		Vector2f temp = myEndPos - myStartPos;
		myStartPos = aPosition;
		myEndPos = myStartPos + temp;
	}

	void LineSegment2D::ChangePosition(const Vector2f aStartPosition, const Vector2f aEndPosition)
	{
		myStartPos = aStartPosition;
		myEndPos = aEndPosition;
	}

	LineSegment2D::~LineSegment2D()
	{
	}

	bool LineSegment2D::IsInside(const Vector2f &aPoint) const
	{
		if ((aPoint - myStartPos).Dot(GetNormal()) <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Vector2f LineSegment2D::GetNormal() const
	{
		Vector2f direction = myEndPos - myStartPos;
		return Vector2f(-direction.y, direction.x).Normalize();
	}

};