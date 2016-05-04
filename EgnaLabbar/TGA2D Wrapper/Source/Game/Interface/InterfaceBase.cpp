#include "stdafx.h"
#include "InterfaceBase.h"


InterfaceBase::InterfaceBase()
{
	myRenderPriority = 100.f;
	myShowInterface = true;
	myName = "No Name";
}


InterfaceBase::~InterfaceBase()
{
}

void InterfaceBase::Draw()const
{
	if (GetIsShowing() == true)
	{
		BaseGameObject::Draw();
	}
}

void InterfaceBase::SetShowInterface(bool aShow)
{
	myShowInterface = aShow;
}

bool InterfaceBase::GetIsShowing() const
{
	return myShowInterface;
}

void InterfaceBase::SetIsShowing(bool aValue)
{
	myShowInterface = aValue;
}

std::string InterfaceBase::Getname()
{
	return myName;
}

