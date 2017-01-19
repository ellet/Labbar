#pragma once

#include "Steering.h"

class BaseController;

class BaseBehaviour
{
public:
	BaseBehaviour(const BaseController & aController);
	~BaseBehaviour();

	virtual Steering UpdateSteering(const float aDeltaTime) = 0;

protected:
	SB::Vector2f GetPosition() const;

private:
	const BaseController * myController;
};

