#pragma once
#include "Items\ItemTypesEnum.h"
#include "../Stats/Buff.h"
#include "../../Structs/name_and_description.h"

struct Item
{
	NameAndDescription itemNameAndDescription;
	enumEquipTypes myItemType;

	Buff itemBuff;
};