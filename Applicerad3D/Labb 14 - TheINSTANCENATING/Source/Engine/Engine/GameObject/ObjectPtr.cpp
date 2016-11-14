#include "stdafx.h"
#include "ObjectPtr.h"
#include "GameObject.h"
#include "Engine/Scene/Scene.h"

namespace ENGINE_NAMESPACE
{
	ObjectPtr::~ObjectPtr()
	{
		if (myPointer != nullptr)
		{
			int count = myReferenceCounter->fetch_sub(1);

			if (count == 1)
			{
				ReturnObject();
			}

			myPointer = nullptr;
			myReferenceCounter = nullptr;
		}
	}

	void ObjectPtr::ReturnObject()
	{
		myPointer->GetScene().ReturnObject(*myPointer);
		myPointer = nullptr;
	}

	bool ObjectPtr::operator==(const ObjectPtr & aOtherPointer) const
	{
		return (myPointer == aOtherPointer.myPointer);
	}

	bool ObjectPtr::operator!=(const ObjectPtr & aOtherPointer) const
	{
		return !(myPointer == aOtherPointer.myPointer);
	}

	bool ObjectPtr::operator==(const GameObject * aOtherPointer) const
	{
		return (myPointer == aOtherPointer);
	}

	bool ObjectPtr::operator!=(const GameObject * aOtherPointer) const
	{
		return !(myPointer == aOtherPointer);
	}

	bool ObjectPtr::operator==(std::nullptr_t aNullptr) const
	{
		return (myPointer == nullptr);
	}

	bool ObjectPtr::operator!=(std::nullptr_t aNullptr) const
	{
		return !(myPointer == nullptr);
	}

	ObjectPtr::ObjectPtr(GameObject *aPointer, std::atomic<int> * aRefCounter)
	{
		myPointer = aPointer;
		myReferenceCounter = aRefCounter;

		if (myPointer != nullptr)
		{
			if (myPointer->GetIdentifier() == "Node 4")
			{
				std::cout << "node 4 stuff" << std::endl;
			}
		}
	}

	ObjectPtr::ObjectPtr()
	{
		myReferenceCounter = nullptr;
		myPointer = nullptr;
	}

	ObjectPtr::ObjectPtr(const ObjectPtr &aOtherPointer)
	{
		myPointer = aOtherPointer.myPointer;
		myReferenceCounter = aOtherPointer.myReferenceCounter;
		if (myPointer != nullptr)
		{
			if (myPointer->GetIdentifier() == "Node 4")
			{
				std::cout << "node 4 stuff" << std::endl;
			}
			myReferenceCounter->fetch_add(1);
		}
	}

	ObjectPtr::ObjectPtr(std::nullptr_t aNullptr) : ObjectPtr()
	{
	}

	ObjectPtr::ObjectPtr(const GameObject *aPointer, std::atomic<int> * aRefCounter)
	{
		myPointer = const_cast<SB::GameObject*>(aPointer);
		myReferenceCounter = aRefCounter;
	}

	//inline ObjectPtr::ObjectPtr(ObjectPtr && aOtherPointer)
	//{
	//	myPointer = aOtherPointer.myPointer;
	//	myReferenceCounter = aOtherPointer.myReferenceCounter;
	//
	//	aOtherPointer.myPointer = nullptr;
	//	aOtherPointer.myReferenceCounter = nullptr;
	//}

	ObjectPtr & ObjectPtr::operator=(const ObjectPtr & aOtherPointer)
	{
		if (myPointer != nullptr)
		{
			int refCount = myReferenceCounter->fetch_sub(1);
			if (refCount == 1)
			{
				ReturnObject();
			}
		}
		myPointer = aOtherPointer.myPointer;
		myReferenceCounter = aOtherPointer.myReferenceCounter;
		if (myPointer != nullptr)
		{
			if (myPointer->GetIdentifier() == "Node 4")
			{
				std::cout << "node 4 stuff" << std::endl;
			}
			myReferenceCounter->fetch_add(1);
		}
		return *this;
	}

	//inline ObjectPtr & ObjectPtr::operator=(ObjectPtr && aOtherPointer)
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

	GameObject * ObjectPtr::operator->()
	{
		return myPointer;
	}

	GameObject * ObjectPtr::operator->() const
	{
		return myPointer;
	}

	GameObject & ObjectPtr::operator*()
	{
		return *myPointer;
	}

	GameObject & ObjectPtr::operator*() const
	{
		return *myPointer;
	}
}
