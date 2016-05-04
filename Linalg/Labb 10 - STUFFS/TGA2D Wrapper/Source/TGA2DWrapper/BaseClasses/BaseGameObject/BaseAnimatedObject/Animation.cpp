#include "Animation.h"

Animation::Animation()
{

	myFirstFrame = 0;
	myFrameCount = 0;
	myDisplayTime = 0.f;

}

Animation::Animation(const unsigned short aFirstFrame, const unsigned short aFrameCount, const float aDisplayTime)
{

	myFirstFrame = aFirstFrame;
	myFrameCount = aFrameCount;
	myDisplayTime = aDisplayTime;

}
Animation::~Animation()
{
}
