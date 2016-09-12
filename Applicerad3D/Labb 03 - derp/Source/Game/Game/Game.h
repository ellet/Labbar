#pragma once
#include "Model/HUGModel.h"

class CGame
{
public:
	CGame();
	~CGame();

	void Init();

	void Update();

	void Render();

private:
	CHUGModel myTriangle;
	CHUGModel myQuad;
};

