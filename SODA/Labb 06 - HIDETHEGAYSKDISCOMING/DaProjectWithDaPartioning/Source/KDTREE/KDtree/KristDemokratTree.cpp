#include "stdafx.h"
#include "KristDemokratTree.h"



KDTree::KDTree()
{
	myMaxDepth = 0;
	myRootNode = nullptr;
}

KDTree::~KDTree()
{

}

void KDTree::Init(
	const CU::GrowingArray<CU::Vector2f> & aArrayOfObjectPositions, 
	const CU::GrowingArray<float> & aArrayOfRaidua)
{
	myPointOfView.Init();

	myCircles.Init(aArrayOfObjectPositions.Size());
	myCircles.Resize(aArrayOfObjectPositions.Size());	

	for (unsigned short iCircle = 0; iCircle < aArrayOfObjectPositions.Size(); ++iCircle)
	{
		myCircles[iCircle].Init(aArrayOfObjectPositions[iCircle], aArrayOfRaidua[iCircle]);
	}


}

void KDTree::BuildTree(const CU::Vector2f & aTreeArea, int aMaxDepth)
{
	myMaxDepth = aMaxDepth;

	CU::GrowingArray<Circle*> tempCircles;
	tempCircles.Init(myCircles.Size());

	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		tempCircles.Add(&myCircles[iCircle]);
	}

	CU::Vector4f tempRekt(0.f,0.f,aTreeArea.x, aTreeArea.y);

	if (myRootNode != nullptr)
	{
		DeleteNodes(*myRootNode);
	}
	myRootNode = BuildTreeNode(tempCircles, tempRekt, 0, false);
}


void KDTree::SetupPointOfView(const CU::Vector2f & aStartPoint, const CU::Vector2f & aEndPoint)
{
	myPointOfView.SetPointOfView(aStartPoint, aEndPoint);
}

void KDTree::CullingPointOfView()
{
	for (unsigned short iObject = 0; iObject < myCircles.Size(); ++iObject)
	{
		myCircles[iObject].Reset();
		if (Intersection2D::TriangleVSCircle(myPointOfView.GetTriangle(), myCircles[iObject].GetSphere()) == true)
		{
			myCircles[iObject].SetIsSeen();
		}
	}

}

KDNode * KDTree::BuildTreeNode(const CU::GrowingArray<Circle*>& aRelevantCircles, const CU::Vector4f & aNodeREKT, const int aCurrentDepth, bool aIsX)
{
	KDNode * tempNode = new KDNode();
	tempNode->myREKT = aNodeREKT;
	if (aCurrentDepth < myMaxDepth && aRelevantCircles.Size() > 1)
	{

		unsigned short workIndex = 0;
		if (aIsX == false)
		{
			workIndex = 1;
		}

		CU::GrowingArray<Circle*> sortedCircles;
		CU::GrowingArray<float> tempXValue;
		tempXValue.Init(aRelevantCircles.Size());

		CU::GrowingArray<float> tempYValue;
		tempYValue.Init(aRelevantCircles.Size());

		sortedCircles.Init(aRelevantCircles.Size());
		for (unsigned short iCircle = 0; iCircle < aRelevantCircles.Size(); ++iCircle)
		{
			bool added = false;
			Circle & circleToAdd = *aRelevantCircles[iCircle];
			const CU::Vector2f CirleToAddPosition = circleToAdd.GetPosition();

			for (unsigned short iSorted = 0; iSorted < sortedCircles.Size(); ++iSorted)
			{
				const CU::Vector2f CirleToCheckPosition = sortedCircles[iSorted]->GetPosition();

				float tempx = CirleToAddPosition.x;
				float tempy = CirleToAddPosition.y;
				float tempvalue = CirleToAddPosition[workIndex];


				if (CirleToAddPosition[workIndex] < CirleToCheckPosition[workIndex])
				{
					sortedCircles.Insert(iSorted, &circleToAdd);
					tempXValue.Insert(iSorted, circleToAdd.GetPosition().x);
					tempYValue.Insert(iSorted, circleToAdd.GetPosition().y);
					added = true;
					break;
				}
			}

			if (added == false)
			{
				sortedCircles.Add(&circleToAdd);
				tempXValue.Add(circleToAdd.GetPosition().x);
				tempYValue.Add(circleToAdd.GetPosition().y);
			}
		}
		
		unsigned short middleRightIndex = sortedCircles.Size() / 2;
		unsigned short middleLeftIndex = middleRightIndex - 1;
		Circle & leftCircle = *sortedCircles[middleLeftIndex];
		Circle & rightCircle = *sortedCircles[middleRightIndex];

		//float lengthBetweenCircles = rightCircle.GetPosition()[workIndex] - leftCircle.GetPosition()[workIndex];
		float lengthBetweenCircles = (rightCircle.GetPosition()[workIndex] + rightCircle.GetRadius()) - (leftCircle.GetPosition()[workIndex] - leftCircle.GetRadius());

		const float LinePositionOnAxis = leftCircle.GetPosition()[workIndex] + (lengthBetweenCircles / 2.f);

		CU::Vector2f startPosition(aNodeREKT.x, aNodeREKT.y);
		CU::Vector2f endPosition(aNodeREKT.z, aNodeREKT.w);

		startPosition[workIndex] = LinePositionOnAxis;
		endPosition[workIndex] = LinePositionOnAxis;

		Intersection2D::LineSegment2D splitterLine(startPosition, endPosition);
		tempNode->mySplit = splitterLine;

		CU::GrowingArray<Circle*> aLeftCircles;
		CU::GrowingArray<Circle*> aRightCircles;
		aLeftCircles.Init(sortedCircles.Size() / 2);
		aRightCircles.Init(sortedCircles.Size() / 2);

		CU::GrowingArray<Circle*>* workArray = &aLeftCircles;
		CU::GrowingArray<Circle*>* otherArray = &aRightCircles;
		for (unsigned short iCircle = 0; iCircle < sortedCircles.Size(); ++iCircle)
		{
			if (iCircle > middleLeftIndex && workArray == &aLeftCircles)
			{
				std::swap(workArray, otherArray);
			}

			CU::Vector2f tempDerp;
			if (Intersection2D::LineVsCircle(splitterLine, sortedCircles[iCircle]->GetSphere(), tempDerp) == true)
			{
				otherArray->Add(sortedCircles[iCircle]);
			}
			workArray->Add(sortedCircles[iCircle]);
		}

		CU::Vector2f rightREKTLeftCorner(aNodeREKT.x, aNodeREKT.y);
		rightREKTLeftCorner[workIndex] = LinePositionOnAxis;

		CU::Vector2f leftREKTRightCorner(aNodeREKT.z, aNodeREKT.w);
		leftREKTRightCorner[workIndex] = LinePositionOnAxis;

		CU::Vector4f leftRekt(aNodeREKT.x, aNodeREKT.y, leftREKTRightCorner.x, leftREKTRightCorner.y);
		CU::Vector4f rightRekt(rightREKTLeftCorner.x, rightREKTLeftCorner.y, aNodeREKT.z, aNodeREKT.w);

		tempNode->myLeftNode = BuildTreeNode(aLeftCircles, leftRekt, aCurrentDepth + 1, !aIsX);
		tempNode->myRightNode = BuildTreeNode(aRightCircles, rightRekt, aCurrentDepth + 1, !aIsX);
		return tempNode;
	}
	
	for (unsigned short iCircles = 0; iCircles < aRelevantCircles.Size(); ++iCircles)
	{
		tempNode->myObjects.Add(aRelevantCircles[iCircles]);
	}

	return tempNode;
}



void KDTree::DrawNodes(const KDNode & aNodeToDraw) const
{
	if (aNodeToDraw.myLeftNode != nullptr)
	{
		DrawNodes(*aNodeToDraw.myLeftNode);
	}

	if (aNodeToDraw.myRightNode != nullptr)
	{
		DrawNodes(*aNodeToDraw.myRightNode);
	}

	DRAWLINE(aNodeToDraw.mySplit.myStartPos, aNodeToDraw.mySplit.myEndPos);

	/*const CU::Vector2f UpperLeft(aNodeToDraw.myREKT.x, aNodeToDraw.myREKT.y);
	const CU::Vector2f LowerRight(aNodeToDraw.myREKT.z, aNodeToDraw.myREKT.w);
	const CU::Vector2f UpperRight(aNodeToDraw.myREKT.z, aNodeToDraw.myREKT.y);
	const CU::Vector2f LowerLeft(aNodeToDraw.myREKT.x, aNodeToDraw.myREKT.w);

	DRAWLINE(UpperLeft, UpperRight);
	DRAWLINE(UpperRight, LowerRight);
	DRAWLINE(LowerRight, LowerLeft);
	DRAWLINE(LowerLeft, UpperLeft);*/
}

void KDTree::DeleteNodes(const KDNode & aNodeToDelete)
{
	if (aNodeToDelete.myLeftNode != nullptr)
	{
		DeleteNodes(*aNodeToDelete.myLeftNode);
	}

	if (aNodeToDelete.myRightNode != nullptr)
	{
		DeleteNodes(*aNodeToDelete.myRightNode);
	}

	delete &aNodeToDelete;
}

void KDTree::Update(const CU::Time & aTime)
{
	CullingPointOfView();
}

void KDTree::Draw() const
{
	myPointOfView.Draw();
	myCircles.CallFunctionOnAllMembers(std::mem_fn(&Circle::Draw));
	DrawNodes(*myRootNode);
}
