#pragma once
#include "Engine/Component/Factory/BaseComponentFactory.h"
#include "Utilities/Memory/MemoryPool.h"

namespace ENGINE_NAMESPACE
{
	template <typename TComponentType>
	class ComponentFactory : public BaseComponentFactory
	{
	public:
		ComponentFactory(const unsigned short aGrowAmount = 256);
		~ComponentFactory();

		TComponentType & CreateComponent(unsigned short * aIndex = nullptr);

		bool Prepare(bool aLoadAsynchronously) override;

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render() const override;

		virtual void DebugUpdate(const Time & aDeltaTime) override;
		virtual void DebugRender() const override;

		virtual void ReturnMemory(unsigned short aIndex) override;

		template <typename TEnumerator>
		void EnumerateActiveComponents(const TEnumerator & aEnumerator);

		template <typename TEnumerator>
		void EnumerateActiveComponents(const TEnumerator & aEnumerator) const;

		int Count() const;

	private:
		DynamicMemoryPool<TComponentType> myComponentPool;
	};

	template <typename TComponentType>
	int ComponentFactory<TComponentType>::Count() const
	{
		return myComponentPool.Count();
	}

	template <typename TComponentType>
	template <typename TEnumerator>
	void ComponentFactory<TComponentType>::EnumerateActiveComponents(const TEnumerator & aEnumerator)
	{
		myComponentPool.ForEach([&aEnumerator](TComponentType & aComponent) -> void
		{
			if (aComponent.IsEnabled() == true)
			{
				aEnumerator(aComponent);
			}
		});
	}

	template <typename TComponentType>
	template <typename TEnumerator>
	void ComponentFactory<TComponentType>::EnumerateActiveComponents(const TEnumerator & aEnumerator) const
	{
		myComponentPool.ForEach([&aEnumerator](TComponentType & aComponent) -> void
		{
			if (aComponent.IsEnabled() == true)
			{
				aEnumerator(aComponent);
			}
		});
	}


	template <typename TComponentType>
	ComponentFactory<TComponentType>::~ComponentFactory()
	{
		EnumerateActiveComponents([](TComponentType & aComponent) -> void
		{
			Error(FormatString("A component of type {0} was never returned.", typeid(TComponentType).name()));
		});
	}

	template <typename TComponentType>
	ComponentFactory<TComponentType>::ComponentFactory(const unsigned short aGrowAmount)
		: myComponentPool(aGrowAmount)
	{
	}

	template <typename TComponentType>
	void ComponentFactory<TComponentType>::ReturnMemory(unsigned short aIndex)
	{
		myComponentPool.Free(aIndex);
	}

	template <typename TComponentType>
	TComponentType & ComponentFactory<TComponentType>::CreateComponent(unsigned short * aIndex /*= nullptr */)
	{
		return myComponentPool.Allocate(aIndex);
	}

	template <typename TComponentType>
	bool ComponentFactory<TComponentType>::Prepare(bool aLoadAsynchronously)
	{
		if (typeid(&BaseComponent::Prepare) == typeid(&TComponentType::Prepare))
			return true;

		bool isReady = true;

		EnumerateActiveComponents([&isReady, aLoadAsynchronously] (TComponentType & aComponent)
		{
			if (aComponent.Prepare(aLoadAsynchronously) == false)
			{
				isReady = false;
			}
		});
		
		return isReady;
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::Update(const Time & aDeltaTime)
	{
		if (typeid(&BaseComponent::Update) == typeid(&TComponentType::Update))
			return;

		EnumerateActiveComponents([&](TComponentType & aComponent)
		{
			aComponent.Update(aDeltaTime);
		});
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::Render() const
	{
		if (typeid(&BaseComponent::Render) == typeid(&TComponentType::Render))
			return;

		EnumerateActiveComponents([&](TComponentType & aComponent)
		{
			aComponent.Render();
		});
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::DebugUpdate(const Time & aDeltaTime)
	{
		if (typeid(&BaseComponent::DebugUpdate) == typeid(&TComponentType::DebugUpdate))
			return;

		EnumerateActiveComponents([&](TComponentType & aComponent)
		{
			aComponent.DebugUpdate(aDeltaTime);
		});
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::DebugRender() const
	{
		if (typeid(&BaseComponent::DebugRender) == typeid(&TComponentType::DebugRender))
			return;
		
		EnumerateActiveComponents([&](TComponentType & aComponent)
		{
			aComponent.DebugRender();
		});
	}
}
