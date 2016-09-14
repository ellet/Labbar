#pragma once
#include "Model/HUGModel.h"
#include "Camera/Camera.h"

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
	CHUGModel myCube;

	Camera myCamera;
};
