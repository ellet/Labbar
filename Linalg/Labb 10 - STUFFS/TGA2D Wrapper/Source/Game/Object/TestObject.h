#pragma once
#include <BaseClasses/BaseGameObject/BaseGameObject.h>
#include <CollisionManager/CollisionShapes/SweptCircle.h>


class TestObject : public BaseGameObject
{
public:
	TestObject();
	~TestObject();

	void Init(const Vector2f & aPosition, const Vector2f & aSpeed);

	void OnCollision(const CollisionData & aCollisonData) override;

	void MoveObject(const float aDeltaTime);

	void ApplyGravitation(const float aDeltaTime);

	virtual void Update(const float aDeltaTime) override;

	void UpdateCollisionBox(Vector2f aNewPosition);


private:
	Vector2f mySpeed;
	Vector2f myPreviousPosition;

	SweptCircle myCollisionShape;
};

