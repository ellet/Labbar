#include "stdafx.h"
#include "OctoTree.h"
#include "QuadTree/OctoNode.h"
#include <CU/Intersection/Intersection2D.h>

OctoTree::OctoTree()
{
	myRootNode = nullptr;
}


OctoTree::~OctoTree()
{
}

void OctoTree::Init(const CU::GrowingArray<CU::Vector3f> & aArrayOfPositions)
{
	OctoNode::ourLooseness = 1.2f;
	myPointOfView.Init();
	myIncstructionSprite = new StaticSprite();
	myIncstructionSprite->Init("Sprites/instructions.png");

	myCircles.Init(aArrayOfPositions.Size());
	myCircles.Resize(aArrayOfPositions.Size());
	Randomizer randoooom;

	for (unsigned short iCircle = 0; iCircle < aArrayOfPositions.Size(); ++iCircle)
	{
		myCircles[iCircle].Init(aArrayOfPositions[iCircle], randoooom.GetRandomValue(6.f, 24.f));
	}
}

void OctoTree::Update(const CU::Time & aTime)
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		myCircles[iCircle].Update(aTime);
	}

	UpdateObjectTreeLocation();

	CollisionCheck();

	myPointOfView.Update(aTime);
}

void OctoTree::Draw() const
{
	myCircles.CallFunctionOnAllMembers(std::mem_fn(&Circle::Draw));
	myPointOfView.Draw();
	myIncstructionSprite->Draw(CU::Vector2f(500.f, 760.f));

}





OctoNode * OctoTree::CreateNode(const CU::Vector3f &aCenter, float aHalfWidth, float aLooseness, const int aCurrentDepth, OctoNode * aParent)
{
	if (aCurrentDepth >= myMaxDepth)
	{
		return nullptr;
	}

	OctoNode * newNode = new OctoNode();
	newNode->myParent = aParent;
	newNode->myCenter = aCenter;
	newNode->myHalfWidth = aHalfWidth;

	newNode->myBox.myCenterPos = aCenter;
	newNode->myBox.myExtents = CU::Vector3f(aHalfWidth, aHalfWidth, aHalfWidth);
	newNode->myBox.myMinPos = aCenter - newNode->myBox.myExtents;
	newNode->myBox.myMaxPos = aCenter + newNode->myBox.myExtents;

	newNode->myLooseBox.myCenterPos = aCenter;
	newNode->myLooseBox.myExtents = CU::Vector3f(aHalfWidth * aLooseness, aHalfWidth * aLooseness, aHalfWidth * aLooseness);
	newNode->myLooseBox.myMinPos = aCenter - newNode->myLooseBox.myExtents;
	newNode->myLooseBox.myMaxPos = aCenter + newNode->myLooseBox.myExtents;



	newNode->myColor = GetColor(aCurrentDepth);

	const float NewWidth = aHalfWidth * 0.5f;
	CU::Vector3f newCenter;

	for (unsigned short iNode = 0; iNode < 8; ++iNode)
	{
		newCenter.x = aCenter.x + (NewWidth * (-1 + (2 * (iNode % 2) )));
		newCenter.y = aCenter.y + (NewWidth * (-1 + (2 * (iNode / 2) )));
		newCenter.z = aCenter.z + (NewWidth * (-1 + (2 * (iNode / 4))));


		newNode->myChildren[iNode] = CreateNode(newCenter, NewWidth, aLooseness, aCurrentDepth + 1, newNode);
	}

	return newNode;
	return nullptr;
}

void OctoTree::AddAllObjects()
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		AddObject(&myCircles[iCircle], myRootNode);
	}
}

void OctoTree::UpdateObjectTreeLocation()
{
	/*for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		Circle & workCircle = myCircles[iCircle];
		if (workCircle.GetParentNode() != myRootNode)
		{
			AddObject(&workCircle, workCircle.GetParentNode()->myParent);
		}
	}*/
}

void OctoTree::DeleteAllNodes()
{
	if (myRootNode != nullptr)
	{
		DeleteNode(myRootNode);
		myRootNode = nullptr;
	}
}

void OctoTree::DeleteNode(OctoNode * aNode)
{
	if (aNode == nullptr)
	{
		return;
	}

	for (int iNode = 0; iNode <= aNode->myChildren.GetSize(); ++iNode)
	{
		DeleteNode(aNode->myChildren[iNode]);
	}

	delete aNode;
}

void OctoTree::CollisionCheckNode(OctoNode * aNode)
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		if (myCircles[iCircle].CollisionTest(myPointOfView) == true)
		{		
			myCircles[iCircle].SetIsSeen();
		}
	}

	/*for (unsigned short iDweller = 0; iDweller < aNode->myDwellers.Size(); ++iDweller)
	{
		if (aNode->myDwellers[iDweller]->CollisionTest(myPointOfView) == true)
		{
			Circle & tempCircle = *aNode->myDwellers[iDweller];

			tempCircle.SetIsSeen();	
		}
	}

	if (aNode->myChildren[0] != nullptr)
	{
		for (unsigned short iNode = 0; iNode <= aNode->myChildren.GetSize(); ++iNode)
		{
			if (Intersection3D::AABBvsSphere(aNode->myChildren[iNode]->myBox, myPointOfView.GetSphere()) == true)
			{
				CollisionCheckNode(aNode->myChildren[iNode]);
			}
		}
		
	}*/
}

void OctoTree::CollisionCheck()
{
	CollisionCheckNode(myRootNode);
}

void OctoTree::AddObject(Circle * aCircle, OctoNode * aStartNode)
{
	OctoNode * currentNodeToCheck = aStartNode;

	bool isPlaced = false;
	while (isPlaced == false)
	{
		bool testInsideLooseBool = Intersection3D::SphereIsInsideAABB(aCircle->GetSphere(), currentNodeToCheck->myLooseBox);
		bool testInsideBoxBool = Intersection3D::PointInsideAABB(currentNodeToCheck->myBox, aCircle->GetSphere().myCenterPosition);
		bool testHaveChildrenBool = currentNodeToCheck->myChildren[0] == nullptr;


		if (Intersection3D::SphereIsInsideAABB(aCircle->GetSphere(), currentNodeToCheck->myLooseBox) == false ||
			Intersection3D::PointInsideAABB( currentNodeToCheck->myBox, aCircle->GetSphere().myCenterPosition) == false ||
			currentNodeToCheck->myChildren[0] == nullptr)
		{
			
			currentNodeToCheck->myDwellers.Add(aCircle);
			aCircle->SetColor(currentNodeToCheck->myColor);
			aCircle->SetParentNode(currentNodeToCheck);
			isPlaced = true;


		}
		else
		{
			CU::Vector3f offset = aCircle->GetSphere().myCenterPosition - currentNodeToCheck->myBox.myCenterPos;

			unsigned short childIndex = 0;

			if (offset.x > 0.f)
			{
				++childIndex;
			}

			if (offset.y > 0.f)
			{
				childIndex += 2;
			}

			if (offset.z > 0.f)
			{
				childIndex += 4;
			}

			currentNodeToCheck = currentNodeToCheck->myChildren[childIndex];
		}

		/*const CU::Vector3f OffsetDistance = aCircle->GetPosition() - currentNodeToCheck->myCenter - currentNodeToCheck->myBox.myExtents;
		const CU::Vector3f DistanceFromCenter = aCircle->GetPosition() - currentNodeToCheck->myCenter;
		
		if ((currentNodeToCheck->myChildren[0] == nullptr) 
			|| 
			(abs(OffsetDistance.x) < aCircle->GetRadius()
			|| abs(OffsetDistance.y) < aCircle->GetRadius()
			|| abs(OffsetDistance.z) < aCircle->GetRadius())
			&& 
			(abs(DistanceFromCenter.x) < currentNodeToCheck->myHalfWidth &&
			abs(DistanceFromCenter.y) < currentNodeToCheck->myHalfWidth &&
			abs(DistanceFromCenter.z) < currentNodeToCheck->myHalfWidth))
		{
			currentNodeToCheck->myDwellers.Add(aCircle);
			aCircle->SetColor(currentNodeToCheck->myColor);
			aCircle->SetParentNode(currentNodeToCheck);
			isPlaced = true;
		}
		else
		{
			unsigned short childIndex = 0;

			if (DistanceFromCenter.x > 0.f)
			{
				++childIndex;
			}

			if (DistanceFromCenter.y > 0.f)
			{
				childIndex += 2;
			}

			if (DistanceFromCenter.z > 0.f)
			{
				childIndex += 4;
			}

			currentNodeToCheck = currentNodeToCheck->myChildren[childIndex];
		}*/
	}
}

void OctoTree::BuildTree(const CU::Vector3f & aAreaSize, const int aMax)
{
	myMaxDepth = aMax;
	myArea = aAreaSize;

	DeleteAllNodes();
	myRootNode = CreateNode(aAreaSize / 2.f, aAreaSize.x / 2.f, OctoNode::ourLooseness, 0, nullptr);
}

void OctoTree::SetPointOfView(const CU::Vector2f & aPosition)
{
	myPointOfView.SetPosition(aPosition);
}

void OctoTree::SetPointOfViewRotation(const CU::Vector3f & aRotation)
{
	myPointOfView.SetRotation(aRotation);
}

void OctoTree::SetLooseNess(const float aDelta)
{
	OctoNode::ourLooseness += aDelta;

	std::cout << OctoNode::ourLooseness << std::endl;

	if (OctoNode::ourLooseness < 1.f)
	{
		OctoNode::ourLooseness = 1.f;
	}

	std::cout << OctoNode::ourLooseness << std::endl;

	BuildTree(myArea, myMaxDepth);
}

CU::Vector4f OctoTree::GetColor(const int aDepth)
{
	CU::Vector4f tempVector;

	switch (aDepth)
	{
	case 0:
		tempVector = CU::Vector4f(1.f, 0.f, 0.f, 1.f);
		break;
	case 1:
		tempVector = CU::Vector4f(0.f, 1.f, 0.f, 1.f);
		break;
	case 2:
		tempVector = CU::Vector4f(0.f, 0.f, 1.f, 1.f);
		break;
	case 3:
		tempVector = CU::Vector4f(1.f, 0.f, 1.f, 1.f);
		break;
	case 4:
		tempVector = CU::Vector4f(0.f, 1.f, 1.f, 1.f);
		break;
	case 5:
		DL_ASSERT(false, "SHOULD NOT GET HERE");
		break;
	}


	return tempVector;
}
