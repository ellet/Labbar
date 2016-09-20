#pragma once
#include "Model/HUGModel.h"
#include "Camera/HUGCameraController.h"

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

	CHUGCameraController myController;
};

