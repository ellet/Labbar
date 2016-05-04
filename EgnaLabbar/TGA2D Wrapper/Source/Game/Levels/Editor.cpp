#include "stdafx.h"
#include "Editor.h"
#include <iostream>

Editor::Editor()
{
	//myEdit = false;
}

void Editor::Update()
{
	if (CommonUtilities::InputWrapper::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft) && myEdit == false)
	{
		std::cout << "BAJS" << std::endl;
	}
	//else if (myInput.GetMouseButtonDown(enumMouseButtons::eRight))
	//{
	//	Vector2f clickedPosition = Vector2f(myInput.GetMouseAbsolutePositionXfloat() / 1024.f, myInput.GetMouseAbsolutePositionYfloat() / 768.f);
	//	for (unsigned int i = 0; i < myBorderList.Size(); i++)
	//	{
	//		if (GetDistance(myBorderList[i].GetNode1(), clickedPosition) < 0.05f)
	//		{
	//			myBorderList[i].DragNode1(clickedPosition);
	//		}
	//		else if (GetDistance(myBorderList[i].GetNode2(), clickedPosition) < 0.05f)
	//		{
	//			myBorderList[i].DragNode2(clickedPosition);
	//		}
	//	}
	//}
	//if (myInput.GetKeyPressed(DIK_E))
	//{
	//	if (myEditActive == true)
	//	{
	//		myEditActive = false;
	//	}
	//	else
	//	{
	//		myEditActive = true;
	//	}
	//}

	//if (myInput.GetMouseButtonPressed(enumMouseButtons::eLeft))
	//{
	//	float x1 = myInput.GetMouseAbsolutePositionXfloat() / 1024.f;
	//	float y1 = myInput.GetMouseAbsolutePositionYfloat() / 768.f;

	//	for (unsigned int i = 0; i < myBorderList.Size(); i++)
	//	{
	//		if (IsNearBorder(myBorderList[i], Vector2f(x1, y1)))
	//		{
	//			Border tempBorder = myBorderList[i];
	//			float value = (GetDistance(tempBorder.GetNode1(), Vector2f(x1, y1))) / tempBorder.GetLength();
	//			myBorderList.Insert(i, Border(tempBorder.GetNode1(), Vector2f(x1, y1)));
	//			myBorderList.Insert(i, Border(Vector2f(x1, y1), tempBorder.GetNode2()));
	//			myBorderList.RemoveCyclicAtIndex(i + 2);
	//			break;
	//		}
	//	}

	//	//myGotoPosition = Vector2f(myInput.GetMouseAbsolutePositionXfloat() / 1024.f, myInput.GetMouseAbsolutePositionYfloat() / 768.f);
	//	FindPath(aDeltaTime);
	//}

	//myPlayer.SetPosition(myPlayer.GetPosition() + myVelocity);

	//for (size_t i = 0; i < myBorderList.Size(); i++)
	//{
	//	if (IsNearBorder(myBorderList[i], myPlayer.GetPosition()) == true)
	//	{
	//		myVelocity.x = 0;
	//		myVelocity.y = 0;
	//	}
	//}

	//if (GetDistance(myPlayer.GetPosition(), myGotoPosition) < 0.03f)
	//{
	//	myVelocity.x = 0;
	//	myVelocity.y = 0;
	//}

	//myPlayer.SetSize(Vector2f(myPlayer.GetPosition().y * 3, myPlayer.GetPosition().y * 3));

}
// WALK CODE 
/*

if (aInput.GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft) && myEdit == false)
{
	myGotoPosition = Vector2f(myInput.GetMouseAbsolutePositionXfloat() / 1024.f, myInput.GetMouseAbsolutePositionYfloat() / 768.f);
	FindPath(aDeltaTime);
}

*/


Editor::~Editor()
{
}
