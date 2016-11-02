#pragma once
#include "Vector2.h"
class Entity
{
public:
	Entity();
	~Entity();

	const CommonUtilities::Vector2f& GetPosition() const;
	const CommonUtilities::Vector2f& GetMoveToPosition() const;
	const CommonUtilities::Vector2f& GetSize() const;
	const CommonUtilities::Vector2f& GetVelocity() const;
	void PhysicsUpdate(const float aDeltaTime);
	virtual void ApplyPosition();

protected:
	void SetPosition(const CommonUtilities::Vector2f & aPosition);
	void SetMoveToPosition(const CommonUtilities::Vector2f & aPosition);
	void SetSize(const CommonUtilities::Vector2f & aSize);
	void SetVelocity(const CommonUtilities::Vector2f & aVelocity);

private:
	CommonUtilities::Vector2f myPosition;
	CommonUtilities::Vector2f myMoveToPosition;
	CommonUtilities::Vector2f mySize;
	CommonUtilities::Vector2f myVelocity;
};

inline const CommonUtilities::Vector2f & Entity::GetPosition() const
{
	return myPosition;
}

inline const CommonUtilities::Vector2f & Entity::GetMoveToPosition() const
{
	return myMoveToPosition;
}

inline const CommonUtilities::Vector2f& Entity::GetSize() const
{
	return mySize;
}

inline const CommonUtilities::Vector2f& Entity::GetVelocity() const
{
	return myVelocity;
}

