#include "stdafx.h"
#include "MainSingleton.h"
#include "CU/Systems/MainSingleton/BaseSingletons/BaseRenderer.h"


namespace CommonUtilities
{
	MainSingleton * MainSingleton::ourInstance = nullptr;

	void MainSingleton::Create()
	{
		DL_ASSERT(ourInstance == nullptr, "Tried to create Main Singleton more than once! It already exists");
		ourInstance = new MainSingleton();
	}

	void MainSingleton::Destroy()
	{
		DL_ASSERT(ourInstance != nullptr, "Tried to Destroy Main Singleton, but it was not created!");
		SAFE_DELETE(ourInstance);
	}

	CommonUtilities::InputWrapper & MainSingleton::GetInputWrapper()
	{
		return GetInstance().myInputWrapper;
	}

	CommonUtilities::TimeManager & MainSingleton::GetTimerManager()
	{
		return GetInstance().myTimeManager;
	}

	const Time & MainSingleton::GetDeltaTime()
	{
		return GetInstance().myTimeManager.GetDeltaTime();
	}

	MainSingleton::MainSingleton()
	{
	}

	MainSingleton::~MainSingleton()
	{
	}

	MainSingleton & MainSingleton::GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "Main Singleton instance is nullptr!");
		return *ourInstance;
	}

}