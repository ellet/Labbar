#include "stdafx.h"
#include "SingletonIsometricInputWrapper.h"
#include <CU/Camera/Camera2D.h>
#include <PostMaster/SingletonPostMaster.h>
#include <CU/Utility/Math/Isometric.h>
#include <Message/WindowRectChangedMessage.h>
#include <Message/SetMainCameraMessage.h>


SingletonIsometricInputWrapper * SingletonIsometricInputWrapper::ourInstance = nullptr;


void SingletonIsometricInputWrapper::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SingletonIsometricInputWrapper();
	}
}


void SingletonIsometricInputWrapper::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}


SingletonIsometricInputWrapper::SingletonIsometricInputWrapper()
{
	SingletonPostMaster::AddReciever(RecieverTypes::eWindowProperties, *this);
	SingletonPostMaster::AddReciever(RecieverTypes::eCamera, *this);
}


SingletonIsometricInputWrapper::~SingletonIsometricInputWrapper()
{
	SingletonPostMaster::RemoveReciever(RecieverTypes::eWindowProperties, *this);
	SingletonPostMaster::RemoveReciever(RecieverTypes::eCamera, *this);
}

CU::Vector2f SingletonIsometricInputWrapper::ConvertMouseNormalizedPositionCartesianCordiante(const bool aOffsetToMiddle/* = false*/) const
{
	CU::Vector2f mousePosition = GetMouseInViewportNormalized();

	if (aOffsetToMiddle == true)
	{
		mousePosition.x -= 0.5f;
		mousePosition.y -= 0.5f;
	}

	mousePosition.x = mousePosition.x * (800.f);
	mousePosition.y = mousePosition.y * (800.f);

	return mousePosition;
}

/*
	Gets mouse position in tilecordinates. adapted to camera and viewport.
*/
CU::Vector2f SingletonIsometricInputWrapper::GetMouseWindowPositionIsometric()
{
	CU::Vector2f mousePosition = GetInstance().ConvertMouseNormalizedPositionCartesianCordiante(true);

	CU::Vector2f newPos = CU::PixelToIsometric(mousePosition);

	newPos = GetInstance().myCameraToAdjustTo->GetPosition() + newPos;

	return newPos;
}


CU::Vector2f SingletonIsometricInputWrapper::GetMouseInViewportNormalized() const
{
	CU::Vector2f mousePosition = myInputWrapper.GetMouseWindowPosition();

	mousePosition.x -= myViewPortSettings.x;
	mousePosition.y -= myViewPortSettings.y;

	mousePosition.x /= (myWindowRect.z - (myViewPortSettings.x * 2.f));
	mousePosition.y /= (myWindowRect.w - (myViewPortSettings.y * 2.f));

	return mousePosition;
}

void SingletonIsometricInputWrapper::Initialize(HINSTANCE aApplicationInstance, HWND aWindow)
{
	GetInstance().myInputWrapper.Initialize(aApplicationInstance, aWindow);
}

void SingletonIsometricInputWrapper::Update()
{
	GetInstance().myInputWrapper.Update();
}

bool SingletonIsometricInputWrapper::RecieveMessage(const WindowRectChangedMessage & aMessage)
{
	DL_PRINT("input received window size");
	myViewPortSettings = aMessage.myViewPortRect;
	myWindowRect = aMessage.myWindowRect;
	return true;
}

bool SingletonIsometricInputWrapper::RecieveMessage(const SetMainCameraMessage & aMessage)
{
	myCameraToAdjustTo = &aMessage.myCamera;
	return true;
}