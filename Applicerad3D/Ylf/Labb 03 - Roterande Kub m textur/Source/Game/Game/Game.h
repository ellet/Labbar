#pragma once
#include "Model/HUGModel.h"
#include "Camera/HUGCameraInterface.h"

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
	CHUGModel myCube;

	CHUGCameraInterface myCamera;
};

