#pragma once

#include <DLDebug\DL_Debug.h>
#include <GrowingArray\GrowingArray.h>

#include "..\BaseGameObject\BaseGameObject.h"

class FactoryGameObject
{
public:

	static void Create();
	static void Destroy();

	template<typename TYPE>
	inline static TYPE* CreateObject();
	template<typename TYPE>
	inline static void DestroyObject(TYPE *anObject);

private:

	class InternalFactory
	{
	public:

		InternalFactory();
		virtual ~InternalFactory();

	};

	template<typename TYPE>
	class InternalTemplateFactory : public InternalFactory
	{
	public:

		inline static TYPE* CreateObject();
		inline static void DestroyObject(TYPE *anObject);

	private:

		static InternalTemplateFactory *ourInternalInstance;
		
		CommonUtilities::GrowingArray<TYPE*> myObjects;

		inline InternalTemplateFactory();
		inline ~InternalTemplateFactory();

		inline static InternalTemplateFactory* GetInstance();

		inline void AllocateNewObjects(const unsigned short aNumberOfObjects);

	};

	static FactoryGameObject *ourInstance;

	CommonUtilities::GrowingArray<InternalFactory*> myFactories;

	FactoryGameObject();
	~FactoryGameObject();

	inline static FactoryGameObject* GetInstance();

};

inline FactoryGameObject* FactoryGameObject::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "No FactoryGameObject instance.");
	return ourInstance;
}

template<typename TYPE>
inline TYPE* FactoryGameObject::CreateObject()
{
	return InternalTemplateFactory<TYPE>::CreateObject();
}
template<typename TYPE>
inline void FactoryGameObject::DestroyObject(TYPE *anObject)
{
	InternalTemplateFactory<TYPE>::DestroyObject(anObject);
}

template<typename TYPE>
FactoryGameObject::InternalTemplateFactory<TYPE> *FactoryGameObject::InternalTemplateFactory<TYPE>::ourInternalInstance;

template<typename TYPE>
inline TYPE* FactoryGameObject::InternalTemplateFactory<TYPE>::CreateObject()
{
	if (GetInstance()->myObjects.Size() == 0)
	{
		GetInstance()->AllocateNewObjects(4);
	}
	TYPE *object = GetInstance()->myObjects.GetLast();
	GetInstance()->myObjects.RemoveCyclicAtIndex(GetInstance()->myObjects.Size() - 1);
	*object = TYPE();
	return object;
}
template<typename TYPE>
inline void FactoryGameObject::InternalTemplateFactory<TYPE>::DestroyObject(TYPE *anObject)
{
	GetInstance()->myObjects.Add(anObject);
}

template<typename TYPE>
inline FactoryGameObject::InternalTemplateFactory<TYPE>::InternalTemplateFactory()
{
	myObjects.Init(4);
}
template<typename TYPE>
inline FactoryGameObject::InternalTemplateFactory<TYPE>::~InternalTemplateFactory()
{
	myObjects.DeleteAll();
	ourInternalInstance = nullptr;
}

template<typename TYPE>
inline FactoryGameObject::InternalTemplateFactory<TYPE>* FactoryGameObject::InternalTemplateFactory<TYPE>::GetInstance()
{
	if (ourInternalInstance == nullptr)
	{
		ourInternalInstance = new InternalTemplateFactory();
		ourInstance->myFactories.Add(ourInternalInstance);
	}
	return ourInternalInstance;
}

template<typename TYPE>
inline void FactoryGameObject::InternalTemplateFactory<TYPE>::AllocateNewObjects(const unsigned short aNumberOfObjects)
{
	for (unsigned short i = 0; i < aNumberOfObjects; ++i)
	{
		myObjects.Add(new TYPE());
	}
}
