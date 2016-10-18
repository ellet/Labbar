#pragma once

#include "hgefont.h"

class ScoreCounter
{
public:
	ScoreCounter();
	~ScoreCounter();
	void Init();
	void Render();
	void AddScore(int aScore);

private:
	hgeFont* myText;
	int myScore;
};
