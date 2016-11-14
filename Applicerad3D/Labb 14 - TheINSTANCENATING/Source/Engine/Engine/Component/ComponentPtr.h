#pragma once

namespace ENGINE_NAMESPACE
{
	template <typename TComponentType>
	class ComponentPtr
	{
	public:
		ComponentPtr(const ComponentPtr &aOtherPointer);
		//ComponentPtr(ComponentPtr && aOtherPointer);
		ComponentPtr(TComponentType *aPointer, std::atomic<int> * aRefCounter);
		ComponentPtr();
		~ComponentPtr();

		//ComponentPtr & operator=(ComponentPtr && aOtherPointer);
		ComponentPtr & operator=(const ComponentPtr & aOtherPointer);
		bool operator==(std::nullptr_t aNullptr) const;
		bool operator!=(std::nullptr_t aNullptr) const;
		bool operator==(const ComponentPtr & aOtherPointer) const;
		bool operator!=(const ComponentPtr & aOtherPointer) const;

		TComponentType *operator->();
		TComponentType *operator->() const;
		TComponentType &operator*();
		TComponentType &operator*() const;

		template <typename TOldComponentType>
		static ComponentPtr<TComponentType> CastFrom(const ComponentPtr<TOldComponentType> & aOtherPtr);

	private:
		template <typename TOtherPtr>
		friend class ComponentPtr;
		void ReturnObject();
		TComponentType * myPointer;
		std::atomic_int * myReferenceCounter;
	};

	template <typename TComponentType>
	template <typename TOldComponentType>
	ComponentPtr<TComponentType> ComponentPtr<TComponentType>::CastFrom(const ComponentPtr<TOldComponentType> & aOtherPtr)
	{
		ComponentPtr newPtr;
		newPtr.myPointer = dynamic_cast<TComponentType*>(aOtherPtr.myPointer);
		if (aOtherPtr.myPointer != nullptr && newPtr.myPointer == nullptr)
		{
			Error(FormatString("Trying to cast a {0} to a {1}.", typeid(TOldComponentType).name(), typeid(TComponentType).name()));
		}

		newPtr.myReferenceCounter = aOtherPtr.myReferenceCounter;
		newPtr.myReferenceCounter->fetch_add(1);
		return newPtr;
	}

	template <typename TComponentType>
	void ComponentPtr<TComponentType>::ReturnObject()
	{
		myPointer->GetGameObject().GetScene().ReturnObject(myPointer->GetGameObject());
		myPointer = nullptr;
	}

	template <typename TComponentType>
	inline bool ComponentPtr<TComponentType>::operator==(const ComponentPtr & aOtherPointer) const
	{
		return (myPointer == aOtherPointer.myPointer);
	}

	template <typename TComponentType>
	inline bool ComponentPtr<TComponentType>::operator!=(const ComponentPtr & aOtherPointer) const
	{
		return !(myPointer == aOtherPointer.myPointer);
	}

	template <typename TComponentType>
	inline bool ComponentPtr<TComponentType>::operator==(std::nullptr_t aNullptr) const
	{
		return (myPointer == nullptr);
	}

	template <typename TComponentType>
	inline bool ComponentPtr<TComponentType>::operator!=(std::nullptr_t aNullptr) const
	{
		return !(myPointer == nullptr);
	}

	template <typename TComponentType>
	inline ComponentPtr<TComponentType>::ComponentPtr(TComponentType *aPointer, std::atomic<int> * aRefCounter)
	{
		myPointer = aPointer;
		myReferenceCounter = aRefCounter;
	}

	template <typename TComponentType>
	inline ComponentPtr<TComponentType>::ComponentPtr()
	{
		myPointer = nullptr;
		myReferenceCounter = nullptr;
	}

	template <typename TComponentType>
	inline ComponentPtr<TComponentType>::ComponentPtr(const ComponentPtr &aOtherPointer)
	{
		myPointer = aOtherPointer.myPointer;
		myReferenceCounter = aOtherPointer.myReferenceCounter;

		if (myReferenceCounter != nullptr)
		{
			myReferenceCounter->fetch_add(1);
		}
	}

	//template <typename TComponentType>
	//inline ComponentPtr<TComponentType>::ComponentPtr(ComponentPtr && aOtherPointer)
	//{
	//	myPointer = aOtherPointer.myPointer;
	//	myReferenceCounter = aOtherPointer.myReferenceCounter;
	//
	//	aOtherPointer.myPointer = nullptr;
	//	aOtherPointer.myReferenceCounter = nullptr;
	//	ptrId = RegisterPtr();
	//}

	template <typename TComponentType>
	inline ComponentPtr<TComponentType>::~ComponentPtr()
	{
		if (myReferenceCounter != nullptr)
		{
			int count = myReferenceCounter->fetch_sub(1);

			if (count == 1)
			{
				ReturnObject();
			}
		}
	}

	template <typename TComponentType>
	inline ComponentPtr<TComponentType> & ComponentPtr<TComponentType>::operator=(const ComponentPtr & aOtherPointer)
	{
		if (myReferenceCounter != nullptr)
		{
			int refCount = myReferenceCounter->fetch_sub(1);

			if (refCount == 1)
			{
				ReturnObject();
			}
		}

		myReferenceCounter = aOtherPointer.myReferenceCounter;
		myPointer = aOtherPointer.myPointer;
		if (myPointer != nullptr)
		{
			myReferenceCounter->fetch_add(1);
		}
		return *this;
	}

	//template <typename TComponentType>
	//inline ComponentPtr<TComponentType> & ComponentPtr<TComponentType>::operator=(ComponentPtr && aOtherPointer)
	//{
	//	if (myReferenceCounter != nullptr)
	//	{
	//		int refCount = myReferenceCounter->fetch_sub(1) - 1;
	//		if (refCount == 0)
	//		{
	//			ReturnObject();
	//		}
	//	}
	//
	//	myPointer = aOtherPointer.myPointer;
	//	myReferenceCounter = aOtherPointer.myReferenceCounter;
	//
	//	aOtherPointer.myPointer = nullptr;
	//	aOtherPointer.myReferenceCounter = nullptr;
	//	return *this;
	//}

	template <typename TComponentType>
	inline TComponentType * ComponentPtr<TComponentType>::operator->()
	{
		return myPointer;
	}

	template <typename TComponentType>
	inline TComponentType * ComponentPtr<TComponentType>::operator->() const
	{
		return myPointer;
	}

	template <typename TComponentType>
	inline TComponentType & ComponentPtr<TComponentType>::operator*()
	{
		return *myPointer;
	}

	template <typename TComponentType>
	inline TComponentType & ComponentPtr<TComponentType>::operator*() const
	{
		return *myPointer;
	}
}
