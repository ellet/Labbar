#pragma once
#include "../InterfaceClickable.h"

class InventorySlot : InterfaceClickable
{
public:
	InventorySlot();
	~InventorySlot();
	void OnMouseClickEvent() override;
};

