#pragma once
#include <Utilities/Pointer/SharedPtr.h>
#include "Engine/Component/Factory/ComponentFactory.h"

namespace SB
{
	template <typename TPointerType>
	class ComponentPtr : public SharedPtr<TPointerType>
	{
	public:
		ComponentPtr();
		ComponentPtr(BaseComponentFactory * aComponentFactory, unsigned short aComponentIndex, TPointerType *aPointer);

		template <typename TOldPointerType>
		static ComponentPtr<TPointerType> CastFrom(const ComponentPtr<TOldPointerType> & aOtherPtr);

	private:
		template<typename T>
		friend class ComponentPtr;

		static void ReturnFunction(SharedPtr<TPointerType> * aUs);

		BaseComponentFactory * myComponentFactory;
		unsigned short myComponentIndex;
	};

	template <typename TPointerType>
	void ComponentPtr<TPointerType>::ReturnFunction(SharedPtr<TPointerType> * aUs)
	{
		auto ptr = static_cast<ComponentPtr*>(aUs);
		ptr->myComponentFactory->ReturnMemory(ptr->myComponentIndex);
	}

	template <typename TPointerType>
	ComponentPtr<TPointerType>::ComponentPtr()
	{
		myReturnFunction = &ReturnFunction;
	}

	template <typename TPointerType>
	template <typename TOldPointerType>
	ComponentPtr<TPointerType> ComponentPtr<TPointerType>::CastFrom(const ComponentPtr<TOldPointerType> & aOtherPtr)
	{
		ComponentPtr newPtr;
		newPtr.myReferenceCounter = aOtherPtr.myReferenceCounter;
		newPtr.myReferenceCounter->fetch_add(1);
		newPtr.myPointer = static_cast<TPointerType*>(aOtherPtr.myPointer);
		newPtr.myComponentFactory = static_cast<BaseComponentFactory*>(aOtherPtr.myComponentFactory);
		newPtr.myComponentIndex = aOtherPtr.myComponentIndex;
		return newPtr;
	}


	template <typename TPointerType>
	ComponentPtr<TPointerType>::ComponentPtr(BaseComponentFactory * aComponentFactory, unsigned short aComponentIndex, TPointerType *aPointer) : SharedPtr(aPointer)
	{
		myComponentFactory = aComponentFactory;
		myComponentIndex = aComponentIndex;
		myReturnFunction = &ReturnFunction;
	}
}
