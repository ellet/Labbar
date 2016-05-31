#pragma once

class CGame;

public ref class TGARenderer
{
public:
	TGARenderer();

	void StartRendering(System::IntPtr aHandle);

private:
	CGame * myRenderer;
};

