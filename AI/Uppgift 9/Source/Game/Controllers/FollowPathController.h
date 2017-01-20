#pragma once
#include "Behaviours\SeekBehaviour.h"
#include "BaseController.h"


class FollowPathController : public BaseController
{
public:
	FollowPathController(const Actor & aActor);
	~FollowPathController();

	virtual SB::Vector2f Update(const float aDeltaTime) override;

	void SetPath(const SB::GrowingArray<SB::Vector2f> aPath);

	void SetSpeedModifier(const float aTileCost);

private:
	float mySpeedModifier;

	SB::GrowingArray<SB::Vector2f> myPath;

	void SetTargetPosition(const SB::Vector2f & aTargetPosition);

	SeekBehaviour mySeekBehaviour;
};

