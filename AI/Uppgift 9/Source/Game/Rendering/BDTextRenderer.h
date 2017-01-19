#pragma once
#include "BDText.h"

namespace Tga2D
{
	class CText;
}


class BDTextRenderer
{
public:
	static void Create();
	static void Destroy();

	static void Init();

	static void RenderText(const BDText & aTextToRender);

	static void Render();

private:
	static BDTextRenderer * ourInstance;

	static BDTextRenderer & GetInstance()
	{
		return *ourInstance;
	}

	BDTextRenderer();
	~BDTextRenderer();

	Tga2D::CText * myText;
	SB::GrowingArray<BDText> myTextToRender;
};

