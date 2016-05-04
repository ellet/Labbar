#pragma once
#include "BaseShape2D.h"

namespace Intersection2D
{

	class AABB2D : public BaseShape2D
	{
	public:
		AABB2D();
		~AABB2D();

		AABB2D(const Vector2f aCenterPosition, const Vector2f aExtents);

		Vector2f myExtents;
		Vector2f myMinPos;
		Vector2f myMaxPos;

		void SetPosition(const Vector2f aCenterPosition)
		{
			myMainPoint = aCenterPosition;
			CalculateMinMax();
		}

		void SetPositionAndSize(const Vector2f aCenterPosition = Vector2f::Zero, const Vector2f aExtents = Vector2f::Half)
		{
			myExtents = aExtents;
			SetPosition(aCenterPosition);
		}

		void SetWithMaxAndMinPos(const Vector2f aMinPosition, const Vector2f aMaxPosition)
		{
			myMinPos = aMinPosition;
			myMaxPos = aMaxPosition;
		}

		virtual void ChangePosition(const Vector2f aPosition) override;

	private:
		void CalculateMinMax()
		{
			myMinPos = myMainPoint - myExtents;
			myMaxPos = myMainPoint + myExtents;
		}

		void CalculateCenterAndExtents()
		{
			myMainPoint = myMinPos + (myMaxPos / 2);

			myExtents = myExtents - myMinPos;
		}

	};

}