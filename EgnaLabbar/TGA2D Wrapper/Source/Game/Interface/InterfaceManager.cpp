#include "stdafx.h"
#include "InterfaceManager.h"

CommonUtilities::GrowingArray<InterfaceBase*> InterfaceManager::ourInterfaces;
InterfaceManager *InterfaceManager::ourInstance;

InterfaceManager::InterfaceManager()
{
}


InterfaceManager::~InterfaceManager()
{
	ourInterfaces.DeleteAll();
}

void InterfaceManager::Init()
{
	GetInstance().InitInternal();
}

void InterfaceManager::SetInterfaceActive(std::string &aInterfaceName, bool aValue)
{
	GetInstance().InternalSetInterfaceActive(aInterfaceName, aValue);
}

void InterfaceManager::InitInternal()
{
	ourInterfaces.Init(5);
}

void InterfaceManager::InternalSetInterfaceActive(std::string &aInterfaceName, bool aValue)
{
	for (unsigned short i = 0; i < ourInterfaces.Size(); i++)
	{
		if (ourInterfaces[i]->Getname() == aInterfaceName)
		{
			ourInterfaces[i]->SetIsShowing(aValue);
		}
	}
}

void InterfaceManager::Update(const float aDeltaTime)
{
	GetInstance().UpdateInternal(aDeltaTime);
}

void InterfaceManager::UpdateInternal(const float aDeltaTime)
{
	for (unsigned short i = 0; i < ourInterfaces.Size(); i++)
	{
		ourInterfaces[i]->Update(aDeltaTime);
	}
}

void InterfaceManager::Draw()
{
	GetInstance().DrawInternal();
}

void InterfaceManager::DrawInternal()
{
	for (unsigned short i = 0; i < ourInterfaces.Size(); i++)
	{
		ourInterfaces[i]->Draw();
	}
}

void InterfaceManager::AddInterface(InterfaceBase *aInterface)
{
	GetInstance().AddInterfaceInternal(aInterface);
}

void InterfaceManager::AddInterfaceInternal(InterfaceBase *aInterface)
{
	ourInterfaces.Add(aInterface);
}
