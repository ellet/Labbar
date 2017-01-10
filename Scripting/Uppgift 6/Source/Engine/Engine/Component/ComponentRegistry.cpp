#include "stdafx.h"
#include "ComponentRegistry.h"
#include <iostream>
#include "ComponentRegistration.h"

namespace SB
{
	ComponentRegistry * ComponentRegistry::ourInstance = nullptr;

	ComponentRegistry::ComponentRegistry()
	{
	}


	ComponentRegistry::~ComponentRegistry()
	{
	}

	ComponentRegistry & ComponentRegistry::GetInstance()
	{
		if (ourInstance == nullptr)
		{
			ourInstance = new ComponentRegistry();
		}
		return *ourInstance;
	}

	void ComponentRegistry::Register(const ComponentRegistration & aRegistration)
	{
#ifndef Publish
		std::cout << FormatString("Component {0} registered", aRegistration.GetIdentifier()) << std::endl;
#endif
		myRegisteredComponents.emplace(aRegistration.GetIdentifier(), &aRegistration);
	}

	ComponentPtr<BaseComponent> ComponentRegistry::CreateComponent(const std::string& aComponent, const ObjectPtr& aObject, DataNode aProperties)
	{
		auto && it = myRegisteredComponents.find(aComponent);

		if (it != myRegisteredComponents.end())
		{
			return it->second->CreateComponent(aObject, aProperties);
		}
		else
		{
			Error(FormatString("Tried to create a component of an unknown type: {0}", aComponent));
		}
	}
}
