#pragma once
#include "BaseShape2D.h"

namespace Intersection2D
{


	class LineSegment2D : public BaseShape2D
	{
	public:
		LineSegment2D();
		~LineSegment2D();

		LineSegment2D(Vector2f aStartPosition, Vector2f aEndPosition)
		{
			myStartPos = aStartPosition;
			myEndPos = aEndPosition;
		}

		void ChangePosition(const Vector2f aPosition) override;
		void ChangePosition(const Vector2f aStartPosition, const Vector2f aEndPosition);

		bool LineSegment2D::IsInside(const Vector2f &aPoint) const;

		Vector2f GetNormal() const;

		Vector2f myStartPos;
		Vector2f myEndPos;

	};

};