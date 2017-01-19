#pragma once

#include "BaseBehaviour.h"

class SeekBehaviour : public BaseBehaviour
{
public:
	SeekBehaviour(const BaseController & aController);
	~SeekBehaviour();

	virtual Steering UpdateSteering(const float aDeltaTime) override;

	void SetTargetPosition(const SB::Vector2f & aTargetPosition);


private:
	SB::Vector2f myTargetPosition;
};

