#pragma once
#include "BaseMouseAction.h"

class SetPlayerGotoOnClick : public BaseMouseAction
{
public:
	SetPlayerGotoOnClick();
	~SetPlayerGotoOnClick();

	void virtual DoOnRelease() override;
	void virtual DoOnClick() override;
	void virtual DoOnHeld() override;
};
