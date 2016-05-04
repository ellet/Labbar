#include "ScreenResolution.h"

#include <Windows.h>

#include <tga2d\engine.h>

ScreenResolution *ScreenResolution::ourInstance;

const unsigned int constTargetScreenWidth = 1920;
const unsigned int constTargetScreenHeight = 1080;
const float constTargetRatio = static_cast<float>(constTargetScreenWidth) / static_cast<float>(constTargetScreenHeight);

void ScreenResolution::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new ScreenResolution();
		ScreenResolution::UpdateResolution();
	}
}
void ScreenResolution::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;
}

void ScreenResolution::UpdateResolution()
{

	ScreenResolution& instance = GetInstance();

	RECT rectangle;
	if (
		GetWindowRect(*DX2D::CEngine::GetInstance()->GetHWND(), &rectangle) == false
		|| GetClientRect(*DX2D::CEngine::GetInstance()->GetHWND(), &rectangle) == false
		)
	{
		instance.myViewScale = Vector2f(0.f, 0.f);
		instance.myViewTransform = Vector2f(0.f, 0.f);
	}

	const Vector2ui screenSize(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);
	if (instance.myLastWindowSize == screenSize)
	{
		return;
	}
	instance.myLastWindowSize = screenSize;

	float width = static_cast<float>(screenSize.x);
	float height = width / constTargetRatio + .5f;

	if (height > screenSize.y)
	{
		height = static_cast<float>(screenSize.y);
		width = height * constTargetRatio + .5f;
	}

	instance.myViewScale = Vector2f(width / screenSize.x, height / screenSize.y);
	
	instance.myViewTransform = Vector2f((1.f - instance.myViewScale.x) / 2.f, (1.f - instance.myViewScale.y) / 2.f);

}

ScreenResolution::ScreenResolution()
{
}
ScreenResolution::~ScreenResolution()
{
}
