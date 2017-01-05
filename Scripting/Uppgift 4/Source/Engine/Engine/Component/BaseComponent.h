#pragma once
#include "Factory/BaseComponentFactory.h"

namespace SB
{
	class GameObject;
	class GenericEventSubsriber;
	class Camera;

	class BaseComponent : public JsonObject
	{
	public:
		BaseComponent();
		virtual ~BaseComponent() = 0;

		virtual bool Prepare(bool aLoadAsynchronously);

		virtual void BeginUpdate(const Time & aDeltaTime);
		virtual void Update(const Time & aDeltaTime);
		virtual void EndUpdate(const Time & aDeltaTime);
		virtual void Render(const Camera & aCamera) const;

		virtual void Initialize();
		virtual void OnRemoved();

		virtual void LoadData(DataNode aProperties);
		
		virtual void DebugUpdate(const Time & aDeltaTime);
		virtual void DebugRender(const Camera & aCamera) const;

		GameObject & GetGameObject() const;

		void SetGameObject(GameObject & anObject);

		template <typename TComponentType>
		ComponentPtr<TComponentType>AsPointer();

		bool IsEnabled() const;
		void Disable();

	protected:
		GameObject * myObject;
		bool myIsEnabled;
	};


	inline bool BaseComponent::IsEnabled() const
	{
		return myIsEnabled;
	}

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
