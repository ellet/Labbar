#pragma once

#include <string>
#include <memory>

#include <Vectors\vector2.h>
#include <Vectors\vector4.h>

#include "../../CollisionManager/CollisionData/CollisionData.h"
#include "../../CollisionManager/CollisionShapes/BaseCollisionShape.h"

struct CollisionData;

namespace DX2D
{
	class CSprite;
}

class BaseCollisionShape;

class BaseGameObject
{
public:

	BaseGameObject();
	virtual ~BaseGameObject();

	virtual void Update(const float aDeltaTime);
	virtual void Draw() const;
	virtual void OnCollision(const CollisionData & aCollisionData);
	
	inline void SetCollisionPosition(const Vector2f aPosition);


	inline DX2D::CSprite* GetSprite() const;
	void SetSprite(DX2D::CSprite *aSprite);
	void LoadSprite(const std::string &aPathToSprite);

	inline const Vector2f& GetPosition() const;
	inline void SetPosition(const Vector2f &aPosition);

	inline const Vector2f& GetSize() const;
	inline void SetSize(const Vector2f &aSize);

	inline const Vector2f& GetPivot() const;
	inline void SetPivot(const Vector2f &aPivot);

	inline float GetRotation() const;
	inline void SetRotation(const float aRotation);

	inline const Vector4f& GetColor() const;
	inline void SetColor(const Vector4f &aColor);
	
	inline void SetCollisionShape(BaseCollisionShape * const aCollisionShape);
	inline void SetCollisionData(BaseCollisionShape * const aCollisionShape);

protected:

	std::shared_ptr<DX2D::CSprite> mySprite;

	Vector2f myPosition;
	Vector2f mySize;
	Vector2f myPivot;
	CollisionData * myCollisionData;

	float myRotation;

	Vector4f myColors;

};

inline void BaseGameObject::SetCollisionPosition(const Vector2f aPosition)
{
	myCollisionData->myCollisionShape->ChangePosition(aPosition);
}

inline void BaseGameObject::SetCollisionShape(BaseCollisionShape * const aCollisionShape)
{
	myCollisionData->myCollisionShape = aCollisionShape;
}

inline void BaseGameObject::SetCollisionData(BaseCollisionShape * const aCollisionShape)
{
	if (myCollisionData != nullptr)
	{
		delete myCollisionData;
		myCollisionData = nullptr;
	}

	myCollisionData = new CollisionData();

	myCollisionData->myCollisionShape = aCollisionShape;
	myCollisionData->myObject = this;
}

inline DX2D::CSprite* BaseGameObject::GetSprite() const
{
	return mySprite.get();
}

inline const Vector2f& BaseGameObject::GetPosition() const
{
	return myPosition;
}
inline void BaseGameObject::SetPosition(const Vector2f &aPosition)
{
	myPosition = aPosition;
}

inline const Vector2f& BaseGameObject::GetSize() const
{
	return mySize;
}
inline void BaseGameObject::SetSize(const Vector2f &aSize)
{
	mySize = aSize;
}

inline const Vector2f& BaseGameObject::GetPivot() const
{
	return myPivot;
}
inline void BaseGameObject::SetPivot(const Vector2f &aPivot)
{
	myPivot = aPivot;
}

inline float BaseGameObject::GetRotation() const
{
	return myRotation;
}
inline void BaseGameObject::SetRotation(const float aRotation)
{
	myRotation = aRotation;
}

inline const Vector4f& BaseGameObject::GetColor() const
{
	return myColors;
}
inline void BaseGameObject::SetColor(const Vector4f &aColor)
{
	myColors = aColor;
}
