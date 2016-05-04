//#include "stdafx.h"
#include "ActionWheel.h"
#include "../MouseInput/MouseInput.h"
#include <Matriser/matrix33.h>
#include <Macros/Macros.h>

#include "WheelElementalOption.h"
#include "WheelOption.h"
#include "ExamineWheelOption.h"



ActionWheel::ActionWheel()
{
	myWheelOptions.Init(6);
	myWheelOptions.Resize(6);
	myIsActive = false;

	myActiveObject = nullptr;

	myRangeFromCenter = 100.f;
	mySizeOfActionBall = 50.f;

	myWheelOptions[static_cast<unsigned short>(eElementType::eEarth)] = new WheelElementalOption(eElementType::eEarth);
	myWheelOptions[static_cast<unsigned short>(eElementType::eFire)] = new WheelElementalOption(eElementType::eFire);
	myWheelOptions[static_cast<unsigned short>(eElementType::eWater)] = new WheelElementalOption(eElementType::eWater);
	myWheelOptions[static_cast<unsigned short>(eElementType::eWind)] = new WheelElementalOption(eElementType::eWind);
	myWheelOptions[4] = new WheelOption();
	myWheelOptions[5] = new ExamineWheelOption();
	//myWheelOptions[0] = new WheelOption();
	/*myWheelOptions[2] = new WheelOption();

	myWheelOptions[3] = new WheelOption();
	myWheelOptions[4] = new WheelOption();
	myWheelOptions[5] = new WheelOption();

	myWheelOptions[6] = new WheelOption();
	myWheelOptions[7] = new WheelOption();*/

	/*ActivateElementalAction(eElementType::eEarth);
	ActivateElementalAction(eElementType::eFire);
	ActivateElementalAction(eElementType::eWater);*/
	//ActivateElementalAction(eElementType::eWind);
	myWheelOptions[4]->ActiveWheelOption();

	/*myWheelOptions[0]->ActiveWheelOption();
	myWheelOptions[1]->ActiveWheelOption();
	myWheelOptions[2]->ActiveWheelOption();
	myWheelOptions[3]->ActiveWheelOption();
	myWheelOptions[4]->ActiveWheelOption();*/
	/*myWheelOptions[4]->ActiveWheelOption();*/
	//myWheelOptions[3]->ActiveWheelOption();
	//myWheelOptions[5]->ActiveWheelOption();

	MyExaminePath("Sprites/ActionWheel/ActionWheel_Examine.dds");
}


ActionWheel::~ActionWheel()
{
}

void ActionWheel::Update()
{
	if (myIsActive == true)
	{
		for (unsigned short iAction = 0; iAction < myWheelOptions.Size(); ++iAction)
		{
			myWheelOptions[iAction]->Update(myActiveObject);
		}
	}
}

void ActionWheel::Draw()
{
	if (myIsActive == true)
	{
		for (unsigned short iAction = 0; iAction < myWheelOptions.Size(); ++iAction)
		{
			myWheelOptions[iAction]->Draw();
		}
	}
}


void ActionWheel::CheckIfSphereIsFullyInsideWorld(Vector2f & aPositionToCheckAndChange)
{
	if (aPositionToCheckAndChange.x < myRangeFromCenter + mySizeOfActionBall)
	{
		aPositionToCheckAndChange.x = myRangeFromCenter + mySizeOfActionBall;
	}
	else if (aPositionToCheckAndChange.x > 1920.f - myRangeFromCenter - mySizeOfActionBall)
	{
		aPositionToCheckAndChange.x = 1920.f - myRangeFromCenter - mySizeOfActionBall;
	}

	if (aPositionToCheckAndChange.y < myRangeFromCenter + mySizeOfActionBall)
	{
		aPositionToCheckAndChange.y = myRangeFromCenter + mySizeOfActionBall;
	}
	else if (aPositionToCheckAndChange.y > 1080.f - myRangeFromCenter - mySizeOfActionBall)
	{
		aPositionToCheckAndChange.y = 1080.f - myRangeFromCenter - mySizeOfActionBall;
	}
}

void ActionWheel::SetPositions()
{
	Vector2f StartPosition = MouseInput::GetMousePosition();

	CheckIfSphereIsFullyInsideWorld(StartPosition);

	float degress = 360.f / myWheelOptions.Size();

	for (unsigned short iAction = 0; iAction < myWheelOptions.Size(); ++iAction)
	{
		Vector2f setPosition = StartPosition;
		
		setPosition += Vector2f(myRangeFromCenter, 0.f) * Matrix33f::CreateRotateAroundZ(DEGRESS_TO_RADIANSF(degress * iAction));
		
		myWheelOptions[iAction]->SetBoxAndObjectPosition(setPosition);
	}
}