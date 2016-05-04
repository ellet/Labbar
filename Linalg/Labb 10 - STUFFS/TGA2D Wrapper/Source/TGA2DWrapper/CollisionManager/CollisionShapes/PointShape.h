#pragma once
#include "BaseCollisionShape.h"
#include <Vectors/vector2.h>

class PointShape : public BaseCollisionShape
{
public:
	PointShape();
	virtual ~PointShape();

	inline Vector2f GetMyPoint() const;

	PointShape(const Vector2f aPoint)
	{
		myCollisionPoint = aPoint;
	}

	virtual bool CheckCollision(const BaseCollisionShape & aCollisionShape) const override;

	virtual bool CheckShapeVsBox(const BoxShape & aCollisionShape) const override;
	virtual bool CheckShapeVsCircle(const CircleShape & aCollisionShape) const override;

	virtual void ChangePosition(const Vector2f aPosition) override;

private:
	Vector2f myCollisionPoint;
};

inline Vector2f PointShape::GetMyPoint() const
{
	return myCollisionPoint;
}