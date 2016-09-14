#pragma once
#include "Model/HUGModel.h"
#include "Camera/HUGCameraInterface.h"
#include "CU/Utility/Randomizer/Randomizer.h"

class CGame
{
public:
	CGame();
	~CGame();

	void Init();

	void Update();

	void Render();

	void RenderCubeAtPosition(const CU::Vector3f & aPosition, const CU::Vector3f & aScale = CU::Vector3f::One);

private:

	CHUGModel myPrettyModel;

	CHUGCameraInterface myCamera;
	Randomizer myRandomizer;

};

