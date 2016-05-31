#pragma once

class CGame;

public ref class TGARenderer
{
public:
	TGARenderer();

	void StartRendering(System::IntPtr aHandle);

private:
	void RenderLoop();

	CGame * myRenderer;
	System::IntPtr myHandle;

};