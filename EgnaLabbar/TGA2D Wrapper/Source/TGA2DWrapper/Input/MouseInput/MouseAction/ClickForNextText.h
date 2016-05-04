#pragma once
#include "BaseMouseAction.h"


class ClickForNextText : public BaseMouseAction
{
public:
	ClickForNextText();
	~ClickForNextText();

	void virtual DoOnRelease() override;
};

