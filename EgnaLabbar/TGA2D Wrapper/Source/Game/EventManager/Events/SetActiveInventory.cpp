#include "stdafx.h"
#include "SetActiveInventory.h"
#include "../../Interface/InterfaceManager.h"


SetActiveInterface::SetActiveInterface(std::string &aName, bool aValue)
{
	myName = aName;
	myValue = aValue;
}


SetActiveInterface::~SetActiveInterface()
{
}

void SetActiveInterface::OneShotEvent()
{
	InterfaceManager::SetInterfaceActive(myName, myValue);
}
