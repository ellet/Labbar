#pragma once

#include "CU_Vector.h"
#include "VisualRep.h"

class Dot
{
public:
	Dot();
	~Dot();
	void Init(CU::Vector2f aPosition, bool isBigDot);
	void Update();
	void Render();
	bool GetIsBigDot();

private:
	CU::Vector2f myPosition;
	VisualRep myVisualRep;
	bool myIsBigDot;
	float myTimer;
	bool myIsVisible;
};
