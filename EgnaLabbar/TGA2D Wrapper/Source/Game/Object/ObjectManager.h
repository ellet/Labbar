#pragma once
#include <map>
#include <string>
#include <DLDEBUG\DL_Debug.h>
#include <iostream>

class Object;

class ObjectManager
{
public:
	inline static void Add(std::map<std::string, Object*> aObjectsMap);
	inline static void Create();
	inline static void Destroy();
	inline static ObjectManager &GetInstance();
	inline static Object* GetAObject(std::string &aObjectName);
private:
	inline void AddInternal(std::map<std::string, Object*> aObjectsMap);
	inline Object* GetAObjectInternal(std::string &aObjectName);
	static std::map<std::string, Object*> myObjectsMap;
	static ObjectManager *ourInstance;
	ObjectManager();
	~ObjectManager();
};

inline ObjectManager& ObjectManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "ObjectManager is nullptr");
	return (*ourInstance);
}

void ObjectManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new ObjectManager();
	}
}

void ObjectManager::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}

void ObjectManager::Add(std::map<std::string, Object*> aObjectsMap)
{
	GetInstance().AddInternal(aObjectsMap);
}

void ObjectManager::AddInternal(std::map<std::string, Object*> aObjectsMap)
{
	myObjectsMap.insert(aObjectsMap.begin(), aObjectsMap.end());
}

Object* ObjectManager::GetAObject(std::string &aObjectName)
{
	return GetInstance().GetAObjectInternal(aObjectName);
}

Object* ObjectManager::GetAObjectInternal(std::string &aObjectName)
{
	auto object = myObjectsMap.find(aObjectName);
	if (object == myObjectsMap.cend())
	{
		std::string message = "The object: " + aObjectName + "\" could not be found check spelling";
		std::cout << message << std::endl;
		bool f = false;
		DL_ASSERT(f, message.c_str());
	}
	return object->second;
}