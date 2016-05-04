#pragma once
#include "BaseCollisionShape.h"

class PointShape;

class BoxShape : public BaseCollisionShape
{
public:
	BoxShape();
	virtual ~BoxShape();

	BoxShape(const Vector2f aCenterPosition, const Vector2f aExtents);
	BoxShape &operator=(BoxShape &aOtherBox);

	inline const Intersection2D::AABB2D & GetCollisionBox() const;

	virtual bool CheckCollision(const BaseCollisionShape & aCollisionShape) const override;

	virtual bool CheckShapeVsBox(const BoxShape & aCollisionShape) const override;

	virtual bool CheckShapeVsPoint(const PointShape & aPointShape) const;

	virtual void ChangePosition(const Vector2f aPosition) override;

	virtual void DrawCollisionBox() const override;


private:
	Intersection2D::AABB2D myCollisionBox;
};

const Intersection2D::AABB2D & BoxShape::GetCollisionBox() const
{
	return myCollisionBox;
}