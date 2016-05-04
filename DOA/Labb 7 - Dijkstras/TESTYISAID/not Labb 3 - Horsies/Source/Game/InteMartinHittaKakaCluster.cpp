#include "stdafx.h"
#include "InteMartinHittaKakaCluster.h"
#include "Renderer.h"
#include <Utility/Randomizer/Randomizer.h>
#include <Macros/Macros.h>

const size_t MinLink = 1;
const size_t MaxLink = 3;

InteMartinHittaKakaCluster::InteMartinHittaKakaCluster()
{
	myGraphicalNodes.Init(10);
}


InteMartinHittaKakaCluster::~InteMartinHittaKakaCluster()
{
}

void InteMartinHittaKakaCluster::Init()
{
	myRandowmyzerx = new Randomizer();
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
	for (size_t iNode = 0; iNode < myGraphicalNodes.Size(); ++iNode)
	{
		DrawLinksInNode(iNode, aRenderer);
	}
}

void InteMartinHittaKakaCluster::ShowPath(const CU::GrowingArray<size_t> & aPath, const size_t aStartNode)
{
	size_t currentNode = aStartNode;
	for (size_t iLink = 0; iLink < aPath.Size(); ++iLink)
	{
		myGraphicalNodes[currentNode].IsPath();
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

	CU::GrowingArray<size_t> findPath;
	findPath.Init(10);
	size_t myGoal = static_cast<size_t>( myRandowmyzerx->GetRandomValue(1.f, static_cast<float>(myGraphicalNodes.Size() - 1)));

	myCluster.ResetLinks();

	myCluster.Dijkstras(findPath, 0, myGoal);

	ShowPath(findPath, 0);
}

void InteMartinHittaKakaCluster::DrawLinksInNode(const size_t aNode, Renderer & aRenderer)
{
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
}