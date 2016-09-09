#include "stdafx.h"
#include "GameWorld.h"


const float SunRotationSpeed = 45.f;
const float EyeyPosition = 1080.f / 2.f - 33.f;

CGameWorld::CGameWorld() : myLeftEyeCenterPosition(1920.f / 2.f - 10.f, EyeyPosition),
	myRightEyeCenterPosition(1920.f / 2.f + 32.f, EyeyPosition - 1)
{
}


CGameWorld::~CGameWorld()
{
}



void CGameWorld::Init()
{
	CreateObjects();
	myLeftEye.Init("Sprites/eye.dds");
	myLeftEye.SetPosition(myLeftEyeCenterPosition);
	myLeftEye.SetSize(2.f);

	myRightEye.Init("Sprites/eye.dds");
	myRightEye.SetPosition(myRightEyeCenterPosition);
	myRightEye.SetSize(2.f);

	myBackground.Init("Sprites/bed.dds");
	myBackground.SetSize(1.5f);
	myBackground.SetPosition({ 860.f + 22.f, 900.f + 185.f});
	
}


void CGameWorld::CreateObjects()
{
	SpatialObject::ConstructData tempConstructData;
	tempConstructData.myOrbitSpeed = 0;

	tempConstructData.myFilePath = "Sprites/adam.dds";
	tempConstructData.myPosition = { 1920.f / 2.f + 67.f, 1080.f / 2.f + 44.f};
	tempConstructData.myRotationSpeed = SunRotationSpeed;
	tempConstructData.myLocalRotationSpeed = 0.f;
	tempConstructData.mySize = 1.2f;

	mySun.Init(tempConstructData);
	mySun.SetParentSpace(WorldSpace);

	tempConstructData.myFilePath = "Sprites/kaffe.dds";
	tempConstructData.myPosition = { 200.f, 200.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = 0.f;

	myFirstPlanet.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/palm.dds";
	tempConstructData.myPosition = { 450.f, 0.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = 30.f;

	mySecondPlanet.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/labb.dds";
	tempConstructData.myPosition = { -450.f, 200.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = 20.f;

	myThirdPlanet.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/ralle.dds";
	tempConstructData.myPosition = { -120.f, -450.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = -70.f;

	myFourthPlanet.Init(tempConstructData);

	mySun.AddChild(myFirstPlanet);
	mySun.AddChild(mySecondPlanet);
	mySun.AddChild(myThirdPlanet);
	mySun.AddChild(myFourthPlanet);
	tempConstructData.myOrbitSpeed = 0.f;

	tempConstructData.myFilePath = "Sprites/chokladboll.dds";
	tempConstructData.myPosition = { 100.f, 0.f };
	tempConstructData.mySize = 0.5f;

	myMoon.Init(tempConstructData);
	myFirstPlanet.AddChild(myMoon);

	const float tempAwesomeHeadDistance = 100.f;

	tempConstructData.myFilePath = "Sprites/ylf.dds";
	tempConstructData.myPosition = { 0.f, tempAwesomeHeadDistance};
	tempConstructData.mySize = 0.45f;
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = 25.f;

	myYlf.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/nicos.dds";
	tempConstructData.myPosition = { 0.f, -tempAwesomeHeadDistance };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = -50.f;

	myNicos.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/dan.dds";
	tempConstructData.myPosition = { tempAwesomeHeadDistance, 0.f};
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = -90.f;

	myDan.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/l1.dds";
	tempConstructData.myPosition = { -tempAwesomeHeadDistance, 0.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;
	tempConstructData.myOrbitSpeed = -10.f;

	myl1.Init(tempConstructData);

	myThirdPlanet.AddChild(myDan);
	myThirdPlanet.AddChild(myNicos);
	myThirdPlanet.AddChild(myYlf);
	myThirdPlanet.AddChild(myl1);


	
}

void CGameWorld::Update(const CU::Time & aDeltaTime)
{
	const float eyeMoveAmount = 5; 

	PixelPositionFloat tempPlanetPosition = myFirstPlanet.GetPosition();

	myLeftEye.SetPosition(((tempPlanetPosition - myLeftEyeCenterPosition).GetNormalized() * eyeMoveAmount + myLeftEyeCenterPosition));
	myRightEye.SetPosition(((tempPlanetPosition - myRightEyeCenterPosition).GetNormalized() * eyeMoveAmount + myRightEyeCenterPosition));
	mySun.Update(aDeltaTime);
}

void CGameWorld::Draw() const
{
	myBackground.Draw();
	mySun.Draw(CU::Matrix33f());
	myLeftEye.Draw();
	myRightEye.Draw();
}



