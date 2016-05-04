#include "stdafx.h"
#include "InteMartinHittaKakaCluster.h"
#include "Renderer.h"
#include <Utility/Randomizer/Randomizer.h>
#include <Intersection/Intersection2D.h>
#include <Macros/Macros.h>


const size_t MinLink = 1;
const size_t MaxLink = 2;

InteMartinHittaKakaCluster::InteMartinHittaKakaCluster()
{
	myGraphicalNodes.Init(10);
	myGoalNodeID = SIZE_MAX;
	myStartNodeID = SIZE_MAX;
	myPreviousUpdatedNode = SIZE_MAX;
	myIsFindingPath = false;
	myPath.Init(10);
}


InteMartinHittaKakaCluster::~InteMartinHittaKakaCluster()
{
}

void InteMartinHittaKakaCluster::Init()
{
	myRandowmyzerx = new Randomizer();
}

void InteMartinHittaKakaCluster::Update()
{
	
	CU::GrowingArray<size_t> * bestSolution = nullptr;

	if (myIsFindingPath == true)
	{
		bestSolution = &myPath;
		size_t currentNode;
		myIsFindingPath = myCluster.Dijkstras(myPath, myGoalNodeID, currentNode);
		UpdateNode(currentNode);
	}
	
	if (bestSolution != nullptr && myIsFindingPath == false)
	{
		UpdateNode(myGoalNodeID);
		ShowPath(*bestSolution, myGoalNodeID);
	}
}

void InteMartinHittaKakaCluster::AddNodesToRenderer(Renderer & aRendererToAddTo)
{
	for (unsigned short iNode = 0; iNode < myGraphicalNodes.Size(); ++iNode)
	{
		aRendererToAddTo.AddNodeToDraw(myGraphicalNodes[iNode].GetSprite());
	}
}

void InteMartinHittaKakaCluster::GenerateMap(const size_t nodeAmount, const Vector2f & aWorldConstraints)
{
	myCluster.ResetCluster();
	myGraphicalNodes.RemoveAll();

	for (size_t iNode = 0; iNode < nodeAmount; ++iNode)
	{
		size_t tempID = myCluster.CreateNode();
		myGraphicalNodes.Add(GraphicalContent(tempID));
		myGraphicalNodes.GetLast().ConfirmID(myGraphicalNodes.Size() - 1);

		Vector2f tempPosition;
		tempPosition.x = myRandowmyzerx->GetRandomValue(0.f, aWorldConstraints.x);
		tempPosition.y = myRandowmyzerx->GetRandomValue(0.f, aWorldConstraints.y);

		myGraphicalNodes.GetLast().SetPosition(tempPosition);
		if (myGraphicalNodes.Size() > 1)
		{
			size_t randomLinkAmount = static_cast<size_t>(myRandowmyzerx->GetRandomValue(static_cast<float>( MinLink), MIN(static_cast<float>(myGraphicalNodes.Size()), static_cast<float>(MaxLink))));
			for (size_t iLink = 0; iLink < randomLinkAmount; ++iLink)
			{
				CreateARandomLink(myGraphicalNodes.Size() - 1);
			}
		}
	}
}

void InteMartinHittaKakaCluster::CreateARandomLink(const size_t aNode)
{
	size_t tempID = aNode;
	while (tempID == aNode)
	{
		tempID = static_cast<size_t>(myRandowmyzerx->GetRandomValue(0.f, static_cast<float>(myGraphicalNodes.Size())));
	}

	myCluster.CreateLink(myGraphicalNodes[aNode].GetNodeID(), myGraphicalNodes[tempID].GetNodeID());
}

void InteMartinHittaKakaCluster::DrawLinks(Renderer & aRenderer)
{
	for (size_t iLink = 0; iLink < myCluster.myLinks.Size(); ++iLink)
	{
		Vector2f startPos = myGraphicalNodes[myCluster.myLinks[iLink].GetFirstNodeID()].GetPosition();
		Vector2f endPos = myGraphicalNodes[myCluster.myLinks[iLink].GetSecondNodeID()].GetPosition();
		Vector4f linkColor(0.5f, 1.f, 0.3f, 1.f);

		if (myGraphicalNodes[myCluster.myLinks[iLink].GetFirstNodeID()].CheckIfUpdated() == true || myGraphicalNodes[myCluster.myLinks[iLink].GetSecondNodeID()].CheckIfUpdated() == true)
		{
			linkColor = Vector4f(0.f, 1.f, 1.f, 1.f);
		}
		
		if (myGraphicalNodes[myCluster.myLinks[iLink].GetFirstNodeID()].CheckIfPath() == true && myGraphicalNodes[myCluster.myLinks[iLink].GetSecondNodeID()].CheckIfPath() == true)
		{
			linkColor = Vector4f(1.f, 0.f, 0.f, 1.f);
		}

		aRenderer.AddLinkToDraw(LineData(startPos, endPos, linkColor));
	}
}

void InteMartinHittaKakaCluster::PrintNodeValues(Renderer & aRenderer)
{
	for (size_t iNode = 0; iNode < myGraphicalNodes.Size(); ++iNode)
	{
		std::string valueToPrint = "";
		
		size_t tempValue = myCluster.GetNodeValue(iNode);

		if (tempValue != SIZE_MAX)
		{
			myNumberConverter << tempValue;

			valueToPrint = myNumberConverter.str();

			myNumberConverter.clear();
			myNumberConverter.str(std::string());

			aRenderer.PrintText(valueToPrint, myGraphicalNodes[iNode].GetPosition());
		}
	}
}

void InteMartinHittaKakaCluster::UpdateNode(const size_t aCurrentNode)
{
	if (aCurrentNode != myStartNodeID && aCurrentNode != myGoalNodeID)
	{
		myGraphicalNodes[aCurrentNode].WasUpdated();
	}

	if (myPreviousUpdatedNode != SIZE_MAX)
	{
		myGraphicalNodes[myPreviousUpdatedNode].ResetPath();
		
	}
	myPreviousUpdatedNode = aCurrentNode;
}

void InteMartinHittaKakaCluster::ShowPath(const CU::GrowingArray<size_t> & aPath, const size_t aStartNode)
{
	size_t currentNode = aStartNode;
	myGraphicalNodes[myGoalNodeID].IsGoal();
	myGraphicalNodes[myStartNodeID].IsStart();

	for (size_t iLink = 0; iLink < aPath.Size(); ++iLink)
	{
		if (currentNode != myGoalNodeID && currentNode != myStartNodeID)
		{
			myGraphicalNodes[currentNode].IsPath();
		}
		myGraphicalNodes[currentNode].SetPathLinkID(aPath[iLink]);
		currentNode = myCluster.GetOtherNode(currentNode, aPath[iLink]);
	}
}

void InteMartinHittaKakaCluster::FindPath()
{
	for (size_t iNode = 0; iNode < myGraphicalNodes.Size(); ++iNode)
	{
		myGraphicalNodes[iNode].ResetPath();
	}

	myPath.RemoveAll();
	if (myStartNodeID == SIZE_MAX)
	{
		myStartNodeID = static_cast<size_t>(myRandowmyzerx->GetRandomValue(1.f, static_cast<float>(myGraphicalNodes.Size() - 1)));
	}
	if (myGoalNodeID == SIZE_MAX)
	{
		do
		{
			myGoalNodeID = static_cast<size_t>(myRandowmyzerx->GetRandomValue(1.f, static_cast<float>(myGraphicalNodes.Size() - 1)));
		} while (myGoalNodeID == myStartNodeID);
	}


	myCluster.ResetLinks();

	myGraphicalNodes[myStartNodeID].IsStart();
	myGraphicalNodes[myGoalNodeID].IsGoal();

	myCluster.StartDjiktras(myStartNodeID);
	myIsFindingPath = true;
}

bool InteMartinHittaKakaCluster::SetStartNodeWithMouse(const Vector2f & aMouseClickedPosition)
{
	size_t startID = ClickedNode(aMouseClickedPosition);
	if (startID != SIZE_MAX)
	{
		myStartNodeID = startID;
		myGraphicalNodes[myStartNodeID].IsStart();
		return true;
	}
	return false;
}

bool InteMartinHittaKakaCluster::SetGoalNodeWithMouse(const Vector2f & aMouseClickedPosition)
{
	size_t goalID = ClickedNode(aMouseClickedPosition);
	if (goalID != SIZE_MAX && goalID != myStartNodeID)
	{
		myGoalNodeID = goalID;
		myGraphicalNodes[myGoalNodeID].IsGoal();
		return true;
	}
	return false;
}

size_t InteMartinHittaKakaCluster::ClickedNode(const Vector2f & aMouseClickedPosition)
{
	for (size_t iNode = 0; iNode < myGraphicalNodes.Size(); ++iNode)
	{
		if (Intersection2D::PointVsCircle(aMouseClickedPosition, myGraphicalNodes[iNode].GetCollider()) == true)
		{
			return iNode;
		}
	}
	return SIZE_MAX;
}

/*
for (size_t iNode = 0; iNode < myGraphicalNodes.Size(); ++iNode)
{
myGraphicalNodes[iNode].LinkReset();
}

for (size_t iLink = 0; iLink < myCluster.GetNodeLinkCount(aNode); ++iLink)
{
if (myGraphicalNodes[myCluster.GetOtherNode(aNode, iLink)].GetHasNotDrawnLinks() == true)
{

Vector2f startPosition = myGraphicalNodes[aNode].GetPosition();
Vector2f endPosition = myGraphicalNodes[myCluster.GetOtherNode(aNode, iLink)].GetPosition();
Vector4f derpColor(0.5f, 1.f, 0.3f, 1.f);

if (myGraphicalNodes[aNode].GetPathLinkID() == iLink)
{
derpColor = Vector4f(1.f, 0.f, 0.f, 1.f);
}

aRenderer.AddLinkToDraw(LineData(startPosition, endPosition, derpColor));
}
myGraphicalNodes[aNode].SetLinkDrawn();
}
*/