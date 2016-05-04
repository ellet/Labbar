#include "LineShape.h"
#include "BoxShape.h"
#include "CircleShape.h"
#include "SweptCircle.h"

#include <DLDebug/DL_Debug.h>

LineShape::LineShape()
{
}


LineShape::~LineShape()
{
}

bool LineShape::CheckCollision(const BaseCollisionShape & aCollisionShape) const
{
	return aCollisionShape.CheckShapeVsLine(*this);
}

bool LineShape::CheckShapeVsBox(const BoxShape & aCollisionShape) const
{
	bool isFalse = false;
	DL_ASSERT(isFalse, "BOX VS LINE NOT IMPLEMENTED YET");
	(aCollisionShape);
	return false;
}

bool LineShape::CheckShapeVsCircle(const CircleShape & aCollisionShape) const
{
	return Intersection2D::LineVsCircle(myCollisionLine, aCollisionShape.GetCollisionBox(), Vector2f(0.0f, 0.0f));
}

bool LineShape::CheckShapeVsSweptCircle(const SweptCircle & aSweptCircle) const
{
	return Intersection2D::LineVsSweptCircle(myCollisionLine, aSweptCircle.GetCollisionLine(), aSweptCircle.GetRadius());
}

void LineShape::ChangePosition(const Vector2f aPosition)
{
	myCollisionLine.ChangePosition(aPosition);
}

Vector2f LineShape::GetNormal()
{
	Vector2f direction = myCollisionLine.myEndPos - myCollisionLine.myStartPos;
	return Vector2f(-direction.y, direction.x).Normalize();
}

