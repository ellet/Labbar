
#include "stdafx.h"
#include "TestOptimizeTGA.h"
#include "OptimizableTga.h"


void TestOptimizeTGA()
{
	// start timer
	LARGE_INTEGER myClockStarted;
	LARGE_INTEGER myClockEnded;
	LARGE_INTEGER myClockFrequency;
	QueryPerformanceFrequency(&myClockFrequency);
	QueryPerformanceCounter(&myClockStarted);

	Optimizable::Tga32::Image *images[1];
	for (int i = 0; i<1; i++)
	{
		images[i] = Optimizable::Tga32::Load("testimage.tga");
	}

	// stop timer
	QueryPerformanceCounter(&myClockEnded);
	double loadTime = (static_cast<double>(myClockEnded.QuadPart-myClockStarted.QuadPart)/myClockFrequency.QuadPart);
	std::cout << "Load time for images: " << loadTime << std::endl;

	Optimizable::Tga32::Save("hej.tga", images[0]->myWidth, images[0]->myHeight, images[0]->myBitDepth, images[0]->myImage);
	system("PAUSE");


	return;
}

