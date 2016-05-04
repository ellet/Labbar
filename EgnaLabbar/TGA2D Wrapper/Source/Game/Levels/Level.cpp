#include "stdafx.h"
#include "Level.h"
#include "tga2d\sprite\sprite.h"
#include <Macros\Macros.h>
#include <Utility\MouseInputResolutionAdaption.h>
#include "../EventManager/Events/Event.h"

Level::Level()
	: myScaleConstant(1.f), myScaleSlope(0.f)
{
	SetScaleValues(0.f, 1.f, 1080.f, 1.f);
}

Level::~Level()
{
	//SAFE_DELETE(myBackgroundImage);
	myBorderList.RemoveAll();
	myGameObjects.RemoveAll();
}

bool Level::Init(CommonUtilities::GrowingArray<Object*> & aGameObjects, CommonUtilities::GrowingArray<Border> & aBorderList,
	const char* aPathToBackgroundImage, const std::string &aLevelName, bool aIsCurrentLevel, Vector2f &aPlayerStartPosition, std::string &aBackgroundSoundName)
{
	myEditIsActive = false;

	tempImageForReview.LoadSprite("Sprites/Interfaces/Inventory/pelare_placeholder.png");
	tempImageForReview.SetPosition(Vector2f(813, 959));
	myBackgroundSoundName = aBackgroundSoundName;
	myTextRenderer.LoadFont("Font/GameFont.txt");
	myGameObjects.Init(aGameObjects.Size());
	myGameObjects = aGameObjects;
	myLevelName = aLevelName;
	myBackgroundImage.LoadSprite(aPathToBackgroundImage);
	myBackgroundImage.SetPivot(Vector2f::Zero);
	myIsCurrentLevel = aIsCurrentLevel;
	myBorderList.Init(aBorderList.Size());
	myBorderList = aBorderList;
	myPlayerStartPosition = aPlayerStartPosition;
	//TODO:: Add validation
	return true;
}



void Level::SetEditMode()
{
	if (myEditIsActive == true)
	{
		myEditIsActive = false;
	}
	else
	{
		myEditIsActive = true;
	}
}

CommonUtilities::GrowingArray<Border> Level::GetBorderList()
{
	return myBorderList;
}


void Level::Update(float aDeltaTime)
{
	for (unsigned short i = 0; i < myGameObjects.Size(); i++)
	{
		myGameObjects[i]->Update(aDeltaTime);
	}
}
void Level::DrawPole()
{
	if (myLevelName == "Level1")
	{
		//tempImageForReview.Draw();
	}
}
void Level::Draw()
{
	myBackgroundImage.Draw();
	for (unsigned short i = 0; i < myGameObjects.Size(); i++)
	{
		myGameObjects[i]->Draw();
	}
	if (myEditIsActive == true)
	{
			
		myTextRenderer.Draw("x: " + std::to_string(static_cast<int>(MouseFix::GetFixedMousePosition().x)) + " y: " + std::to_string(static_cast<int>(MouseFix::GetFixedMousePosition().y)), Vector2f(MouseFix::GetFixedMousePosition().x+20, MouseFix::GetFixedMousePosition().y), 0.7f, Vector4f(1, 0, 0, 1));
		for (unsigned short i = 0; i < myBorderList.Size(); i++)
		{
			myBorderList[i].Render();
			myTextRenderer.Draw("x:" + std::to_string(static_cast<int>(myBorderList[i].GetNode1().x)) + "y:" + std::to_string(static_cast<int>(myBorderList[i].GetNode1().y)), Vector2f(myBorderList[i].GetNode1().x - 50, myBorderList[i].GetNode1().y - 35), 0.7f, Vector4f(1, 1, 1, 1));
		}
	}
}
void Level::SplitNodes(const Vector2f aMousePosition)
{
	for (unsigned short i = 0; i < myBorderList.Size(); i++)
	{
		if (IsNearBorder(myBorderList[i], aMousePosition))
		{

			Border tempBorder = myBorderList[i];
			//float value = (GetDistance(tempBorder.GetNode1(), aMousePosition)) / tempBorder.GetLength();
			Border firstBorder = Border(tempBorder.GetNode1(), aMousePosition);
			Border secondBorder = Border(aMousePosition, tempBorder.GetNode2());
			myBorderList.Insert(i, firstBorder);
			myBorderList.Insert(i, secondBorder);
			myBorderList.RemoveCyclicAtIndex(i + 2);
			break;
		}
	}
}
void Level::EditNodes(const Vector2f aMousePosition)
{
	for (unsigned short i = 0; i < myBorderList.Size(); i++)
	{
		if (GetDistance(myBorderList[i].GetNode1(), aMousePosition) < 30.f)
		{		
			myBorderList[i].DragNode1(aMousePosition);
		
		}
		else if (GetDistance(myBorderList[i].GetNode2(), aMousePosition) < 30.f)
		{
			myBorderList[i].DragNode2(aMousePosition);	
		}
	}
	
}

float Level::GetDistance(Vector2f aPosition1, Vector2f aPosition2)
{
	return sqrt((aPosition2.x - aPosition1.x)*(aPosition2.x - aPosition1.x) + (aPosition2.y - aPosition1.y)*(aPosition2.y - aPosition1.y));
}

bool Level::IsNearBorder(Border aBorder, Vector2f aPlayerPositionVector)
{
	float tempDistance = GetDistance(aPlayerPositionVector, aBorder.GetNode1());
	tempDistance += GetDistance(aPlayerPositionVector, aBorder.GetNode2());
	if (tempDistance < (aBorder.GetLength() + 10.f))
	{
		return true;
	}
	return false;
}

void Level::UserClickedBorder(bool /*aMouseIsDown*/, Vector2f /*aMousePosition*/)
{
	//for (unsigned short i = 0; i < myBorderList.Size(); i++)
	//{
	//	sqrt((aPosition2.x - aPosition1.x)*(aPosition2.x - aPosition1.x) + (aPosition2.y - aPosition1.y)*(aPosition2.y - aPosition1.y));
	//	myBorderList[i].GetNode1()
	//}
}

const std::string & Level::GetBackgroundSoundName()
{
	return myBackgroundSoundName;
}

bool Level::IsCurrentlyEditing()
{
	return myEditIsActive;
}

void Level::SetIsCurrentLevel(bool aIsCurrentLevel)
{
	myIsCurrentLevel = aIsCurrentLevel;
}

bool Level::GetIsCurrentLevel()
{
	return myIsCurrentLevel;
}

std::string& Level::GetMyLevelName()
{
	return myLevelName;
}

const Vector2f& Level::GetPlayerStartPosition()
{
	return myPlayerStartPosition;
}