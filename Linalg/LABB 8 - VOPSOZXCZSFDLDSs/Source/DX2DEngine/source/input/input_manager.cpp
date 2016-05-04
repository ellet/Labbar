#include "stdafx.h"

#include "input/input_manager.h"
#include "engine.h"
#include "windows/windows_window.h"


std::vector<unsigned char> DX2D::CInputManager::previous(256);
std::vector<unsigned char> DX2D::CInputManager::current(256);

using namespace DX2D;
bool DX2D::CInputManager::myRunThreadedUpdate = true;

POINT DX2D::CInputManager::myThreadedMouseAbsPos;
DX2D::Vector2f DX2D::CInputManager::myThreadedMouseNormalizedPos;

#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

CInputManager::CInputManager()
{
	myMousePosition.Set(0, 0);
	myMouseNormalizedPosition.Set(0, 0);
}


CInputManager::~CInputManager()
{
	myRunThreadedUpdate = false;
	myThreadPoller.join();
}

void DX2D::CInputManager::Init()
{
	myThreadPoller = std::thread(&CInputManager::ThreadedPollUpdate);
	//t1.join();
}

void DX2D::CInputManager::ThreadedPollUpdate()
{
	HWND hwnd = CEngine::GetInstance()->GetWindow().GetWindowHandle();
	Vector2<unsigned int> windowSize = CEngine::GetInstance()->GetWindowSize();
	RECT clientRect;

	while (myRunThreadedUpdate)
	{
		GetKeyState(0);
		GetKeyboardState(&current[0]); // normally do error checking
		
		GetClientRect(hwnd, &clientRect);
		int innerWidth = clientRect.right - clientRect.left;
		int innerHeight = clientRect.bottom - clientRect.top;

		windowSize.x = innerWidth;
		windowSize.y = innerHeight;

		GetCursorPos(&myThreadedMouseAbsPos);
		ScreenToClient(hwnd, &myThreadedMouseAbsPos);

		myThreadedMouseAbsPos.x = MIN(myThreadedMouseAbsPos.x, (int)windowSize.x);
		myThreadedMouseAbsPos.x = MAX(myThreadedMouseAbsPos.x, 0);
		myThreadedMouseAbsPos.y = MIN(myThreadedMouseAbsPos.y, (int)windowSize.y);
		myThreadedMouseAbsPos.y = MAX(myThreadedMouseAbsPos.y, 0);

		myThreadedMouseNormalizedPos =  Vector2f((float)myThreadedMouseAbsPos.x, 1.0f-(float)myThreadedMouseAbsPos.y) / Vector2f((float)windowSize.x, (float)windowSize.y);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void DX2D::CInputManager::Update()
{
	myMutex.lock();
	current.swap(previous);
	myMousePosition.Set(myThreadedMouseAbsPos.x, myThreadedMouseAbsPos.y);
	myMouseNormalizedPosition.Set((myThreadedMouseNormalizedPos.x ) , (-myThreadedMouseNormalizedPos.y ) );
	myMutex.unlock();
}

bool CInputManager::IsKeyDown(unsigned char aKey)
{
	return (previous[aKey] & 0x80) != 0;
}