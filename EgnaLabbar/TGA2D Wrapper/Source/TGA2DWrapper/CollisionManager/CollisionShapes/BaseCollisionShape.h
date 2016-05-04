#pragma once
#include <Intersection/Intersection2D.h>

class BoxShape;

class PointShape;

class LineShape;

class CircleShape;

class SweptCircle;

class BaseCollisionShape
{
public:
	BaseCollisionShape();
	virtual ~BaseCollisionShape();

	virtual bool CheckCollision(const BaseCollisionShape & aCollisionShape) const = 0;

	virtual void DrawCollisionBox() const;

	virtual void ChangePosition(const Vector2f aPosition);

	virtual bool CheckShapeVsBox(const BoxShape & aCollisionShape) const;

	virtual bool CheckShapeVsPoint(const PointShape & aPointShape) const;

	virtual bool CheckShapeVsLine(const LineShape & aLineShape) const;

	virtual bool CheckShapeVsCircle(const CircleShape & aCollisionShape) const;

	virtual bool CheckShapeVsSweptCircle(const SweptCircle & aSweptCircle) const;
};