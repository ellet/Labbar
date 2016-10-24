#pragma once
#include "Factory/BaseComponentFactory.h"

namespace ENGINE_NAMESPACE
{
	class GameObject;
	class GenericEventSubsriber;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent() = 0;

		virtual void Update(const Time & aDeltaTime);
		virtual void Render() const;

		virtual void Initialize();

		virtual void LoadData(DataNode aProperties);
		
		virtual void DebugUpdate(const Time & aDeltaTime);
		virtual void DebugRender() const;

		GameObject & GetGameObject() const;

		void SetGameObject(GameObject & anObject);

		template <typename TComponentType>
		ComponentPtr<TComponentType>AsPointer();
	protected:
		GameObject * myObject;
	};

	template <typename TComponentType>
	ComponentPtr<TComponentType> BaseComponent::AsPointer()
	{
		std::atomic<int> *referenceCounter  = myObject->GetReferenceCounter();
		referenceCounter->fetch_add(1);
		
		return ComponentPtr<TComponentType>::CastFrom(ComponentPtr<BaseComponent>(this, referenceCounter));
	}


	template <typename TComponentType>
	ComponentPtr<BaseComponent> DefaultComponentCreator(const ObjectPtr & aObject, DataNode aProperties)
	{
		ComponentPtr<BaseComponent> component = ComponentPtr<BaseComponent>::CastFrom(aObject->CreateComponent<TComponentType>()) ;
		component->LoadData(aProperties);
		return component;
	}
	
}
