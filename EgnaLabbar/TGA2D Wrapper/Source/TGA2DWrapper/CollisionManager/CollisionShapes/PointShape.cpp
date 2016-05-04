#include "PointShape.h"
#include "BoxShape.h"
#include  "CircleShape.h"

PointShape::PointShape()
{
	myCollisionPoint = Vector2f::Zero;
}


PointShape::~PointShape()
{
}

bool PointShape::CheckCollision(const BaseCollisionShape & aCollisionShape) const
{
	return aCollisionShape.CheckShapeVsPoint((*this));
}

bool PointShape::CheckShapeVsBox(const BoxShape & aCollisionShape) const
{
	return Intersection2D::PointInsideAABB2D(aCollisionShape.GetCollisionBox(), myCollisionPoint) ;
}

bool PointShape::CheckShapeVsCircle(const CircleShape & aCollisionShape) const
{
	return Intersection2D::PointVsCircle(myCollisionPoint, aCollisionShape.GetCollisionBox());
}

void PointShape::ChangePosition(const Vector2f aPosition)
{
	myCollisionPoint = aPosition;
}

