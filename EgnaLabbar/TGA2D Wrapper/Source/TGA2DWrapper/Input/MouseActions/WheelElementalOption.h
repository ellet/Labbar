#pragma once
#include "BaseWheelOption.h"

#include "../../../Game/Object/ElemenTypes.h"

class WheelElementalOption : public BaseWheelOption
{
public:	
	WheelElementalOption(const eElementType aElementType = eElementType::enumLength);
	~WheelElementalOption();

	virtual void Update(Object * aObjectPointer) override;
};