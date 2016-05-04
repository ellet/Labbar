#include "SweptCircle.h"
#include "LineShape.h"

SweptCircle::SweptCircle()
{
}


SweptCircle::SweptCircle(const Vector2f aStartPosition, const Vector2f aEndPosition, const float aRadius)
{
	myLine = Intersection2D::LineSegment2D(aStartPosition, aEndPosition);
	myRadius = aRadius;
}

SweptCircle::~SweptCircle()
{
}





bool SweptCircle::CheckCollision(const BaseCollisionShape & aCollisionShape) const
{
	return aCollisionShape.CheckShapeVsSweptCircle(*this);
}

void SweptCircle::ChangePosition(const Vector2f aStartPosition, const Vector2f aEndPosition)
{
	myLine.ChangePosition(aStartPosition, aEndPosition);
}

bool SweptCircle::CheckShapeVsLine(const LineShape & aLineShape) const
{
	return Intersection2D::LineVsSweptCircle(aLineShape.GetMyLine(), myLine, myRadius);
}
