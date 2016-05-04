#pragma once
#include "InterfaceBase.h"
#include <GrowingArray\GrowingArray.h>
#include <DLDebug\DL_Debug.h>

class InterfaceManager
{
public:
	inline static void Create();
	inline static void Destroy();
	static void AddInterface(InterfaceBase *aInterface);
	static void Update(const float aDeltaTime);
	static void Draw();
	static void Init();
	static void SetInterfaceActive(std::string &aInterfaceName, bool aValue);
	inline static InterfaceManager &GetInstance();
private:
	void AddInterfaceInternal(InterfaceBase *aInterface);
	void UpdateInternal(const float aDeltaTime);
	void DrawInternal();
	void InitInternal();
	void InternalSetInterfaceActive(std::string &aInterfaceName, bool aValue);
	InterfaceManager();
	~InterfaceManager();
	static InterfaceManager *ourInstance;
	static CommonUtilities::GrowingArray<InterfaceBase*> ourInterfaces;
};


inline InterfaceManager& InterfaceManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "EventManager is nullptr");
	return (*ourInstance);
}

void InterfaceManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new InterfaceManager();
	}
}

void InterfaceManager::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}
