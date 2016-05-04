#pragma once

#include <DLDebug\DL_Debug.h>

#include <Vectors\Vector2.h>

class ScreenResolution
{
public:

	static void Create();
	static void Destroy();

	inline static const Vector2f& GetViewTransform();
	inline static const Vector2f& GetViewScale();
	inline static const Vector2ui& GetWindowSize();

	static void UpdateResolution();

private:

	static ScreenResolution *ourInstance;

	Vector2f myViewScale;
	Vector2f myViewTransform;

	//TODO::Detect window size change.
	Vector2ui myLastWindowSize;

	ScreenResolution();
	~ScreenResolution();

	inline static ScreenResolution& GetInstance();

};

inline const Vector2f& ScreenResolution::GetViewScale()
{
	return GetInstance().myViewScale;
}
inline const Vector2f& ScreenResolution::GetViewTransform()
{
	return GetInstance().myViewTransform;
}
inline const Vector2ui& ScreenResolution::GetWindowSize()
{
	return GetInstance().myLastWindowSize;
}

inline ScreenResolution& ScreenResolution::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "No ScreenResolution Instance.");
	return *ourInstance;
}
