#include "stdafx.h"
#include "QuadTree.h"
#include "QuadTree/QuadNode.h"
#include <CU/Intersection/Intersection2D.h>

QuadTree::QuadTree()
{
}


QuadTree::~QuadTree()
{
}

void QuadTree::Init(const CU::GrowingArray<CU::Vector2f> & aArrayOfPositions)
{
	myPointOfView.Init();

	myCircles.Init(aArrayOfPositions.Size());
	myCircles.Resize(aArrayOfPositions.Size());

	for (unsigned short iCircle = 0; iCircle < aArrayOfPositions.Size(); ++iCircle)
	{
		myCircles[iCircle].Init(aArrayOfPositions[iCircle]);
	}
}

void QuadTree::Update(const CU::Time & aTime)
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		myCircles[iCircle].Update(aTime);
	}

	UpdateObjectTreeLocation();

	CollisionCheck();
}

void QuadTree::Draw() const
{
	myCircles.CallFunctionOnAllMembers(std::mem_fn(&Circle::Draw));
	myPointOfView.Draw();
}





QuadNode * QuadTree::CreateNode(const CU::Vector2f &aCenter, float aHalfWidth, const int aCurrentDepth, QuadNode * aParent)
{
	if (aCurrentDepth >= myMaxDepth)
	{
		return nullptr;
	}

	QuadNode * newNode = new QuadNode();
	newNode->myParent = aParent;
	newNode->myCenter = aCenter;
	newNode->myHalfWidth = aHalfWidth;

	newNode->myBox.SetPositionAndSize(aCenter, CU::Vector2f(aHalfWidth, aHalfWidth));

	const float NewWidth = aHalfWidth * 0.5f;
	CU::Vector2f newCenter;

	for (unsigned short iNode = 0; iNode < 4; ++iNode)
	{
		newCenter.x = aCenter.x + (NewWidth * (-1 + (2 * (iNode % 2) )));
		newCenter.y = aCenter.y + (NewWidth * (-1 + (2 * (iNode / 2) )));

		newNode->myChildren[iNode] = CreateNode(newCenter, NewWidth, aCurrentDepth + 1, newNode);
	}

	return newNode;
}

void QuadTree::AddAllObjects()
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		AddObject(&myCircles[iCircle], myRootNode);
	}
}

void QuadTree::UpdateObjectTreeLocation()
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		Circle & workCircle = myCircles[iCircle];
		if (workCircle.GetParentNode() != myRootNode)
		{
			AddObject(&workCircle, workCircle.GetParentNode()->myParent);
		}
	}
}

bool QuadTree::CircleRayCollisionCheck(const Circle & aCircle)
{
	

	

	Intersection2D::LineSegment2D centerRay;
	centerRay.myStartPos = aCircle.GetPosition();
	centerRay.myEndPos = myPointOfView.GetCircle().myMainPoint;

	CU::Vector2f diameterNormal = centerRay.GetNormal() * 25.f;
	CU::Vector2f circleLeftCorner = aCircle.GetPosition() - diameterNormal;
	CU::Vector2f circleRightCorner = aCircle.GetPosition() + diameterNormal;

	Intersection2D::LineSegment2D leftRay;
	leftRay.myStartPos = circleLeftCorner;
	leftRay.myEndPos = myPointOfView.GetCircle().myMainPoint;

	Intersection2D::LineSegment2D rightRay;
	rightRay.myStartPos = circleRightCorner;
	rightRay.myEndPos = myPointOfView.GetCircle().myMainPoint;

	for (unsigned short iRayCheck = 0; iRayCheck < myCircles.Size(); ++iRayCheck)
	{
		if (&myCircles[iRayCheck] != &aCircle)
		{
			if (myCircles[iRayCheck].CollisionTestRay(centerRay) == true &&
				myCircles[iRayCheck].CollisionTestRay(leftRay) == true &&
				myCircles[iRayCheck].CollisionTestRay(rightRay) == true)
			{
				return false;
			}
		}
	}
		
	return true;
}

void QuadTree::CollisionCheckNode(QuadNode * aNode)
{
	for (unsigned short iDweller = 0; iDweller < aNode->myDwellers.Size(); ++iDweller)
	{
		if (aNode->myDwellers[iDweller]->CollisionTest(myPointOfView) == true)
		{
			Circle & tempCircle = *aNode->myDwellers[iDweller];


			if (CircleRayCollisionCheck(tempCircle) == true)
			{
				tempCircle.SetIsSeen();
			}
		}
	}

	if (aNode->myChildren[0] != nullptr)
	{
		for (unsigned short iNode = 0; iNode <= aNode->myChildren.GetSize(); ++iNode)
		{
			if (Intersection2D::AABBvsCircle(aNode->myChildren[iNode]->myBox, myPointOfView.GetCircle()) == true)
			{
				CollisionCheckNode(aNode->myChildren[iNode]);
			}
		}
		
	}
}

void QuadTree::CollisionCheck()
{
	CollisionCheckNode(myRootNode);



	/*for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		if (myCircles[iCircle].CollisionTest(myPointOfView) == true)
		{
			Intersection2D::LineSegment2D tempRay;
			tempRay.myStartPos = myCircles[iCircle].GetPosition();
			tempRay.myEndPos = myPointOfView.GetCircle().myMainPoint;

			bool isSeen = true;
			for (unsigned short iRayCheck = 0; iRayCheck < myCircles.Size(); ++iRayCheck)
			{
				if (iRayCheck != iCircle)
				{
					if (myCircles[iRayCheck].CollisionTestRay(tempRay) == true)
					{
						isSeen = false;
						break;
					}
				}
			}

			if (isSeen == true)
			{
				myCircles[iCircle].SetIsSeen();
			}
		}
	}*/
}

void QuadTree::AddObject(Circle * aCircle, QuadNode * aStartNode)
{
	QuadNode * currentNodeToCheck = aStartNode;

	bool isPlaced = false;
	while (isPlaced == false)
	{
		const CU::Vector2f OffsetDistance = aCircle->GetPosition() - currentNodeToCheck->myCenter;

		if (currentNodeToCheck->myHalfWidth >= aCircle->GetRadius() || OffsetDistance.x > aCircle->GetRadius() 
			|| OffsetDistance.y > aCircle->GetRadius() 
			|| currentNodeToCheck->myChildren[0] == nullptr)
		{
			currentNodeToCheck->myDwellers.Add(aCircle);
			aCircle->SetParentNode(currentNodeToCheck);
			isPlaced = true;
		}
		else
		{
			unsigned short childIndex = 0;

			if (OffsetDistance.x > 0.f)
			{
				++childIndex;
			}

			if (OffsetDistance.y > 0.f)
			{
				childIndex += 2;
			}

			currentNodeToCheck = currentNodeToCheck->myChildren[childIndex];
		}
	}
}

void QuadTree::BuildTree(const CU::Vector2f & aAreaSize, const int aMax)
{
	myMaxDepth = aMax;

	myRootNode = CreateNode(aAreaSize / 2.f, aAreaSize.x / 2.f, 0, nullptr);
}

void QuadTree::SetPointOfView(const CU::Vector2f & aPosition)
{
	myPointOfView.SetPosition(aPosition);
}

void QuadTree::SetPointOfViewRotation(const CU::Vector2f & aPosition)
{
	const float Angle = (aPosition - myPointOfView.GetPosition()).GetAngle();

	myPointOfView.SetRotation(Angle);
}