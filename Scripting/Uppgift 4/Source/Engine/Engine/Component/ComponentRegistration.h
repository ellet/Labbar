#pragma once
#include <string>

namespace
SB
{
	using ComponentCreationFunction = ComponentPtr<BaseComponent>(*)(const ObjectPtr &aObject, DataNode aProperties);

	class ComponentRegistration
	{
	public:
		ComponentRegistration(const char * aComponentIdentifier, ComponentCreationFunction aCreationFunction);
		~ComponentRegistration();

		const std::string & GetIdentifier() const;
		ComponentPtr<BaseComponent> CreateComponent(const ObjectPtr & aObject, DataNode aProperties) const;

	private:
		std::string myIdentifier;
		ComponentCreationFunction myCreationFunction;
	};
}

