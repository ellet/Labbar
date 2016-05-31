#include "TGARenderer.h"
#include <Game.h>
#include <windows.h>

TGARenderer::TGARenderer()
{
	myRenderer = new CGame();
}

void TGARenderer::StartRendering(System::IntPtr aHandle)
{
	myRenderer->Init(static_cast<HWND>(aHandle.ToPointer()));
}