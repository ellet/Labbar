#pragma once
#include "BaseMouseAction.h"

class ActivateActionWheel : public BaseMouseAction
{
public:
	ActivateActionWheel();
	~ActivateActionWheel();

	
	void virtual DoOnRelease() override;
	void virtual DoOnClick() override;

private:

};

