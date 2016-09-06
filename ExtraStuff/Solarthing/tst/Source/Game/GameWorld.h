#pragma once

#include "DrawObjects/SpatialObject.h"
#include "DrawObjects/DrawObject.h"

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();
	

	void Init();
	void CreateObjects();

	void Update(const CU::Time & aDeltaTime); 
	void Draw() const;


private:
	CU::Space WorldSpace;
	SpatialObject mySun;

	SpatialObject myFirstPlanet;
	SpatialObject mySecondPlanet;
	SpatialObject myThirdPlanet;
	SpatialObject myFourthPlanet;

	SpatialObject myYlf;
	SpatialObject myNicos;
	SpatialObject myDan;
	SpatialObject myl1;

	SpatialObject myMoon;

	DrawObject myLeftEye;
	DrawObject myRightEye;
	DrawObject myBackground;

	const CU::Vector2f myLeftEyeCenterPosition;
	const CU::Vector2f myRightEyeCenterPosition;
};