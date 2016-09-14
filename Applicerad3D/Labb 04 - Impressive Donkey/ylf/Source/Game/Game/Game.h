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
	void RenderOneCubeALot();
	void RenderAllTheCubes();
	void RenderPileOfCubes();
	void InitPileOfCubes();

	CHUGModel myCube;
	CU::GrowingArray<CHUGModel> myPileOfCubes;
	CHUGModel myPrettyModel;

	CHUGCameraInterface myCamera;
	Randomizer myRandomizer;

};

