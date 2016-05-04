//#include "stdafx.h"
#include "InputWrapper.h"


namespace CommonUtilities
{

	InputWrapper * InputWrapper::ourInstance;


	void InputWrapper::Create()
	{
		if (ourInstance == nullptr)
		{
			ourInstance = new InputWrapper();
		}
	}


	void InputWrapper::Destroy()
	{
		delete ourInstance;

		ourInstance == nullptr;
	}


	InputWrapper::InputWrapper()
	{
		myKeyboardData.resize(256);
		myPreviousKeyboardData.resize(256);
		myImInitialized = false;
	}


	InputWrapper::~InputWrapper()
	{
		myKeyboard->Unacquire();
		myKeyboard->Release();
		myKeyboard = nullptr;

		myMouse->Unacquire();
		myMouse->Release();
		myMouse = nullptr;

		myInputInterface->Release();
		myInputInterface = nullptr;

	}

	void InputWrapper::Initialize(HINSTANCE aApplicationInstance, HWND aWindow)
	{
		GetInstance().InternalInitialize(aApplicationInstance, aWindow);
	}

	void InputWrapper::Update()
	{
		GetInstance().InternalUpdate();
	}

	void InputWrapper::InternalInitialize(HINSTANCE aApplicationInstance, HWND aWindow)
	{
		HRESULT inputError;
		inputError = DirectInput8Create(aApplicationInstance, DIRECTINPUT_VERSION, IID_IDirectInput8A, reinterpret_cast<void**>(&myInputInterface), nullptr);

		myWindowID = aWindow;

		myInputInterface->CreateDevice(GUID_SysKeyboard, &myKeyboard, nullptr);
		myInputInterface->CreateDevice(GUID_SysMouse, &myMouse, nullptr);

		myKeyboard->SetDataFormat(&c_dfDIKeyboard);
		myKeyboard->SetCooperativeLevel(aWindow, DISCL_BACKGROUND);
		myKeyboard->Acquire();

		myMouse->SetDataFormat(&c_dfDIMouse);
		myMouse->SetCooperativeLevel(aWindow, DISCL_BACKGROUND);
		myMouse->Acquire();

		myImInitialized = true;
	}

	void InputWrapper::InternalUpdate()
	{
		if (myImInitialized == false)
		{
			return;
		}

		myPreviousMouseData = myMouseData;
		myMouse->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&myMouseData));

		myPreviousKeyboardData = myKeyboardData;
		myKeyboard->GetDeviceState(sizeof(BYTE) * myKeyboardData.size(), static_cast<void*>(&myKeyboardData[0]));
	}

}