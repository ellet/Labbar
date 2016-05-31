#include "TGARenderer.h"
#include <Game.h>
#include <windows.h>

using namespace System;
using namespace System::Threading;

TGARenderer::TGARenderer()
{
	myRenderer = new CGame();
}

void TGARenderer::StartRendering(System::IntPtr aHandle)
{
	myHandle = aHandle;
	Thread^ thread1 = gcnew Thread(gcnew ThreadStart(this, &TGARenderer::RenderLoop));
	thread1->Name = "RenderirrrrrngLuuup";
	thread1->Start();
}

void TGARenderer::RenderLoop()
{
	myRenderer->Init(static_cast<HWND>(myHandle.ToPointer()));
}
