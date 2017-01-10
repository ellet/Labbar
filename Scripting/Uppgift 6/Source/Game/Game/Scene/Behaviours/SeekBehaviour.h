#pragma once
#include "BaseBehaviour.h"

struct SetSeekTargetEvent
{
	SetSeekTargetEvent(const SB::Vector2f aPosition) : myTargetPosition(aPosition)
	{}

	

	SB::Vector2f myTargetPosition;
};

class SeekBehaviour : public BaseBehaviour
{
public:
	SeekBehaviour(const Unit & aParentUnit);
	~SeekBehaviour();

	void SetTargetPosition(const SB::Vector2f & aPosition)
	{
		myShouldMoveToTarget = true;
		myTargetPosition = aPosition;
	}

	virtual Steering GetSteering(const SB::Time & aDeltaTime) override;

	static float ourWeight;

private:
	bool myShouldMoveToTarget;
	SB::Vector2f myTargetPosition;
};

