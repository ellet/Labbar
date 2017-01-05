#include "stdafx.h"
#include "ComponentRegistration.h"
#include "ComponentRegistry.h"


namespace
SB
{
	ComponentRegistration::ComponentRegistration(const char * aComponentIdentifier, ComponentCreationFunction aCreationFunction)
	{
		myIdentifier = aComponentIdentifier;
		myCreationFunction = aCreationFunction;
		ComponentRegistry::GetInstance().Register(*this);
	}


	ComponentRegistration::~ComponentRegistration()
	{
	}

	const std::string & ComponentRegistration::GetIdentifier() const
	{
		return myIdentifier;
	}

	ComponentPtr<SB::BaseComponent> ComponentRegistration::CreateComponent(const ObjectPtr& aObject, DataNode aProperties) const
	{
		return myCreationFunction(aObject, aProperties);
	}
}
