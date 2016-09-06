#include "stdafx.h"
#include "MainSingleton.h"

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

	PostMaster & MainSingleton::GetPostMaster()
	{
		return GetInstance().myPostMaster;
	}

	void MainSingleton::SetRenderer(BaseRenderer * aRenderer)
	{
		GetInstance().myRenderer = aRenderer;
	}

	MainSingleton::MainSingleton()
	{
		myRenderer = nullptr;
	}

	MainSingleton::~MainSingleton()
	{
		ASSIGNED_DELETE(myRenderer);
	}

	MainSingleton & MainSingleton::GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "Main Singleton instance is nullptr!");
		return *ourInstance;
	}

}