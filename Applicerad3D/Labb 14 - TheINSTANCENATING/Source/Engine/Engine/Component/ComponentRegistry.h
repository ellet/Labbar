#pragma once

namespace ENGINE_NAMESPACE
{
	class ComponentRegistration;

	class ComponentRegistry
	{
	public:
		ComponentRegistry();
		~ComponentRegistry();
		static ComponentRegistry & GetInstance();

		void Register(const ComponentRegistration & aRegistration);
		ComponentPtr<BaseComponent> CreateComponent(const std::string & aComponent, const ObjectPtr & aObject, DataNode aProperties);

	private:
		static ComponentRegistry * ourInstance;
		std::unordered_map<std::string, const ComponentRegistration*> myRegisteredComponents;
	};
}

