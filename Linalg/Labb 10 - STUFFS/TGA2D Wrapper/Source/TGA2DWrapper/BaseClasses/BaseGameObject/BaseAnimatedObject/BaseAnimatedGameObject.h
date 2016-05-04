#pragma once

#include "..\BaseGameObject.h"

#include <GrowingArray\GrowingArray.h>
#include "Animation.h"

class BaseAnimatedGameObject : public BaseGameObject
{
public:

	typedef unsigned short AnimationHandle;

	BaseAnimatedGameObject();
	virtual ~BaseAnimatedGameObject();

	virtual void Update(const float aDeltaTime);
	virtual void Draw() const;

	inline unsigned short GetColumns() const;
	inline void SetColumns(const unsigned short aNumber);
	inline unsigned short GetRows() const;
	inline void SetRows(const unsigned short aNumber);

	AnimationHandle AddAnimation();
	AnimationHandle AddAnimation(const Animation &anAnimation);
	void PlayAnimtaion(const AnimationHandle anAnimationHandle);
	void ResetAnimation();

private:

	unsigned short myColumns;
	unsigned short myRows;

	AnimationHandle myCurrentAnimation;
	unsigned short myCurrentFrame;
	CommonUtilities::GrowingArray<Animation> myAnimations;

	float myLeftoverDeltaTime;

};

inline unsigned short BaseAnimatedGameObject::GetColumns() const
{
	return myColumns;
}
inline void BaseAnimatedGameObject::SetColumns(const unsigned short aNumber)
{
	myColumns = aNumber;
}
inline unsigned short BaseAnimatedGameObject::GetRows() const
{
	return myRows;
}
inline void BaseAnimatedGameObject::SetRows(const unsigned short aNumber)
{
	myRows = aNumber;
}
