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
	myLeftEye.Init("Sprites/eye.png");
	myLeftEye.SetPosition(myLeftEyeCenterPosition);
	myLeftEye.SetSize(2.f);

	myRightEye.Init("Sprites/eye.png");
	myRightEye.SetPosition(myRightEyeCenterPosition);
	myRightEye.SetSize(2.f);

	myBackground.Init("Sprites/bed.dds");
	myBackground.SetSize(1.5f);
	myBackground.SetPosition({ 860.f, 900.f });
	
}


void CGameWorld::CreateObjects()
{
	SpatialObject::ConstructData tempConstructData;

	tempConstructData.myFilePath = "Sprites/adam.png";
	tempConstructData.myPosition = { 1920.f / 2.f, 1080.f / 2.f };
	tempConstructData.myRotationSpeed = SunRotationSpeed;
	tempConstructData.myLocalRotationSpeed = 0.f;
	tempConstructData.mySize = 1.2f;


	mySun.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/Kaffe.png";
	tempConstructData.myPosition = { 200.f, 200.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myFirstPlanet.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/palm.dds";
	tempConstructData.myPosition = { 450.f, 0.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	mySecondPlanet.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/vg.png";
	tempConstructData.myPosition = { -450.f, 200.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myThirdPlanet.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/Ralle.png";
	tempConstructData.myPosition = { -120.f, -450.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myFourthPlanet.Init(tempConstructData);

	mySun.AddChild(myFirstPlanet);
	mySun.AddChild(mySecondPlanet);
	mySun.AddChild(myThirdPlanet);
	mySun.AddChild(myFourthPlanet);

	tempConstructData.myFilePath = "Sprites/Chokladboll.png";
	tempConstructData.myPosition = { 100.f, 0.f };
	tempConstructData.mySize = 0.5f;

	myMoon.Init(tempConstructData);
	myFirstPlanet.AddChild(myMoon);

	const float tempAwesomeHeadDistance = 100.f;

	tempConstructData.myFilePath = "Sprites/ylf.png";
	tempConstructData.myPosition = { 0.f, tempAwesomeHeadDistance};
	tempConstructData.mySize = 0.45f;
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myYlf.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/Nicos.png";
	tempConstructData.myPosition = { 0.f, -tempAwesomeHeadDistance };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myNicos.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/Dan.png";
	tempConstructData.myPosition = { tempAwesomeHeadDistance, 0.f};
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myDan.Init(tempConstructData);

	tempConstructData.myFilePath = "Sprites/l1.png";
	tempConstructData.myPosition = { -tempAwesomeHeadDistance, 0.f };
	tempConstructData.myRotationSpeed = 60.f;
	tempConstructData.myLocalRotationSpeed = 60.f;

	myl1.Init(tempConstructData);

	myThirdPlanet.AddChild(myDan);
	myThirdPlanet.AddChild(myNicos);
	myThirdPlanet.AddChild(myYlf);
	myThirdPlanet.AddChild(myl1);


	
}

void CGameWorld::Update(const CU::Time & aDeltaTime)
{
	const float eyeMoveAmount = 5; 

	PixelPositionFloat tempPlanetPosition = myFirstPlanet.GetPosition() * mySun.GetTransformation();

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



