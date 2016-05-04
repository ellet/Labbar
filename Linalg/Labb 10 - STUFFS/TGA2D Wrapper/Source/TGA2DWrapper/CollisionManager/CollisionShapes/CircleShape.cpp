#include "CircleShape.h"
#include "LineShape.h"
#include "PointShape.h"

CircleShape::CircleShape()
{
}


CircleShape::CircleShape(const Vector2f aPosition, const float aRadius)
{
	myCircle = Intersection2D::Circle2D(aPosition, aRadius);
}

CircleShape::~CircleShape()
{
}

bool CircleShape::CheckCollision(const BaseCollisionShape & aCollisionShape) const
{
	return aCollisionShape.CheckShapeVsCircle((*this));
}

bool CircleShape::CheckShapeVsPoint(const PointShape & aPointShape) const
{
	return Intersection2D::PointVsCircle(aPointShape.GetMyPoint(), myCircle);
}

bool CircleShape::CheckShapeVsLine(const LineShape & aLineShape) const
{
	return Intersection2D::LineVsCircle(aLineShape.GetMyLine(), myCircle, Vector2f(0.1f, 0.1f));
}

void CircleShape::ChangePosition(const Vector2f aPosition)
{
	myCircle.ChangePosition(aPosition);
}
