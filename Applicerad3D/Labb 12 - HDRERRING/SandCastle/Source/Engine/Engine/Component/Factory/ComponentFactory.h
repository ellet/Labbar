#pragma once
#include "Engine/Component/Factory/BaseComponentFactory.h"

namespace ENGINE_NAMESPACE
{
	template <typename TComponentType>
	class ComponentFactory : public BaseComponentFactory
	{
	public:
		ComponentFactory(const unsigned short aAmountOfItems = 1024);
		~ComponentFactory();

		TComponentType & CreateComponent(unsigned short * aIndex = nullptr);

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render() const override;

		virtual void DebugUpdate(const Time & aDeltaTime) override;
		virtual void DebugRender() const override;

		virtual void ReturnMemory(unsigned short aIndex) override;

		template <typename TEnumerator>
		void EnumerateActiveComponents(const TEnumerator & aEnumerator);

		int Count() const;

	private:
		unsigned short GetAndActivateIndex();

		GrowingArray<bool> myComponentsActiveTag;
		TComponentType * myComponents;
		Stack<unsigned short> myFreeMemorySlots;
		unsigned short myNumberOfComponents;
	};

	template <typename TComponentType>
	int ComponentFactory<TComponentType>::Count() const
	{
		int counter = 0;
		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				counter++;
			}
		}
		return counter;
	}

	template <typename TComponentType>
	template <typename TEnumerator>
	void ComponentFactory<TComponentType>::EnumerateActiveComponents(const TEnumerator & aEnumerator)
	{
		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				aEnumerator(myComponents[iComponent]);
			}
		}
	}


	template <typename TComponentType>
	ComponentFactory<TComponentType>::~ComponentFactory()
	{
		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				Error("A component was never returned! Memory was leaked!");
			}
		}

		free(myComponents);
		myComponents = nullptr;
	}

	template <typename TComponentType>
	ComponentFactory<TComponentType>::ComponentFactory(const unsigned short aAmountOfItems)
	{
		myNumberOfComponents = aAmountOfItems;
		myComponents = static_cast<TComponentType*>(malloc(sizeof(TComponentType) * myNumberOfComponents));
		myComponentsActiveTag.Resize(myNumberOfComponents);
		for (unsigned short i = 0; i < myNumberOfComponents; i++)
		{
			myFreeMemorySlots.Push(i);
			myComponentsActiveTag[i] = false;
		}
	}

	template <typename TComponentType>
	void ComponentFactory<TComponentType>::ReturnMemory(unsigned short aIndex)
	{
		myComponents[aIndex].~TComponentType();
		myFreeMemorySlots.Push(aIndex);
		myComponentsActiveTag[aIndex] = false;
	}

	template <typename TComponentType>
	TComponentType & ComponentFactory<TComponentType>::CreateComponent(unsigned short * aIndex /*= nullptr */)
	{
		unsigned short index = GetAndActivateIndex();
		new (&myComponents[index]) TComponentType();

		if (aIndex != nullptr)
		{
			*aIndex = index;
		}

		return myComponents[index];
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::Update(const Time & aDeltaTime)
	{
		if (typeid(&BaseComponent::Update) == typeid(&TComponentType::Update))
			return;

		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				myComponents[iComponent].Update(aDeltaTime);
			}
		}
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::Render() const
	{
		if (typeid(&BaseComponent::Render) == typeid(&TComponentType::Render))
			return;

		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				myComponents[iComponent].Render();
			}
		}
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::DebugUpdate(const Time & aDeltaTime)
	{
		if (typeid(&BaseComponent::DebugUpdate) == typeid(&TComponentType::DebugUpdate))
			return;

		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				myComponents[iComponent].DebugUpdate(aDeltaTime);
			}
		}
	}

	template <typename TComponentType>
	inline void ComponentFactory<TComponentType>::DebugRender() const
	{
		if (typeid(&BaseComponent::DebugRender) == typeid(&TComponentType::DebugRender))
			return;

		for (unsigned short iComponent = 0; iComponent < myNumberOfComponents; ++iComponent)
		{
			if (myComponentsActiveTag[iComponent] == true)
			{
				myComponents[iComponent].DebugRender();
			}
		}
	}


	template <typename TComponentType>
	unsigned short ComponentFactory<TComponentType>::GetAndActivateIndex()
	{
		if (myFreeMemorySlots.Size() == 0)
		{
			Error(FormatString("Component Factory {0} is empty, tell a programmer it needs more slots!", typeid(TComponentType).name()));
		}
		unsigned short index = myFreeMemorySlots.Pop();
		myComponentsActiveTag[index] = true;
		return index;
	}
}
