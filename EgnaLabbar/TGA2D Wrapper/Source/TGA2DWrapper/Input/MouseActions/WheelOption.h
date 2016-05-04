#pragma once
#include "BaseWheelOption.h"

class WheelOption : public BaseWheelOption
{
public:
	WheelOption();
	virtual ~WheelOption();

	virtual void Update(Object * aObjectPointer) override;

	


};

