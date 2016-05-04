#pragma once
#include "BaseWheelOption.h"

class ExamineWheelOption : public BaseWheelOption
{
public:
	ExamineWheelOption();
	~ExamineWheelOption();

	virtual void Update(Object * aObjectPointer) override;
};

