#pragma once
#include "BaseController.h"
#include "Input\InputListener.h"



class PlayerController : public BaseController
{
public:
	PlayerController(const Actor & aActor);
	~PlayerController();

	virtual SB::Vector2f Update(const float aDeltaTime) override;

private:
	InputListener myInputListener;
};

