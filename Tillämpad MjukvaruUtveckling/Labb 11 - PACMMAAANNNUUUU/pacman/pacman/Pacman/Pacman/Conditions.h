#pragma once

#include "hgefont.h"

class Conditions
{
public:
	Conditions();
	~Conditions();
	void Init();

	bool GetReady(int aLife);
	bool YouLose(int aLife);
	bool YouWin(int someDotLeft);
	void Render();

private:
	hgeFont* myFont;
	char* myText;
	bool myIsVisible;
	float myGetReadyTimer;
	int myLastPlayerLife;
	float myTimer;

};
