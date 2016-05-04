#include "GraphCluster.h"


CommonUtilities::GraphCluster::GraphCluster()
{
	myNodes.Init(10);
	myLinks.Init(20);
}

CommonUtilities::GraphCluster::~GraphCluster()
{
}

size_t CommonUtilities::GraphCluster::CreateNode()
{
	myNodes.Add(Node());
	myNodes.GetLast().SetID(myNodes.Size() - 1);
	return myNodes.Size() - 1;
}

void CommonUtilities::GraphCluster::CreateLink(const size_t aFirstNodeID, const size_t aSecondNodeID)
{
	myLinks.Add(Link(aFirstNodeID, aSecondNodeID));
	myNodes[aFirstNodeID].AddLink(myLinks.Size() - 1);
	myNodes[aSecondNodeID].AddLink(myLinks.Size() - 1);
}

void CommonUtilities::GraphCluster::ResetLinks()
{
	for (size_t iLink = 0; iLink < myLinks.Size(); ++iLink)
	{
		myLinks[iLink].Reset();
	}
}

size_t CommonUtilities::GraphCluster::GetOtherNode(const size_t aNodeID, const size_t aLinkID)
{
	return myLinks[myNodes[aNodeID].myLinksIDs[aLinkID]].GetOtherNode(aNodeID);
}

void CommonUtilities::GraphCluster::AddLinksToPathOptions(const size_t aNodeID)
{
	for (size_t iLink = 0; iLink < myNodes[aNodeID].myLinksIDs.Size(); ++iLink)
	{
		Node::NodeValue & value = myNodes[GetOtherNode(aNodeID, iLink)].myValueCounter;
		size_t cost = myNodes[aNodeID].myValueCounter.myValue + myLinks[myNodes[aNodeID].myLinksIDs[iLink]].GetCost();
		if (cost < value.myValue)
		{
			value.myValue = cost;
			if (myNodes[GetOtherNode(aNodeID, iLink)].IsInHeap() == false)
			{
				myNodes[GetOtherNode(aNodeID, iLink)].SetToInHeap();
				myPathOptions.Enqueue(&value);
			}
			else
			{
				myPathOptions.Resort();
			}
		}
		
	}
}

void CommonUtilities::GraphCluster::Dijkstras(CommonUtilities::GrowingArray<size_t> & aPath, const size_t aStartNode, const size_t aGoalNode)
{

	for (size_t iNode = 0; iNode < myNodes.Size(); ++iNode)
	{
		myNodes[iNode].ResetValueCounter();
	}

	myNodes[aStartNode].SetValueCounter(0);
	AddLinksToPathOptions(aStartNode);

	while (myPathOptions.IsEmpty() == false)
	{
		size_t currentNode = myPathOptions.Dequeue()->myNodeID;
		myNodes[currentNode].SetToNotInHeap();
		AddLinksToPathOptions(currentNode);
	}

	size_t currentPosition = aGoalNode;
	do
	{
		aPath.Add(FindShortest(currentPosition));
		
	} while (myNodes[currentPosition].myValueCounter.myValue != 0);
}

size_t CommonUtilities::GraphCluster::FindShortest(size_t& aCurrentNode)
{
	Node::NodeValue bestValue = myNodes[GetOtherNode(aCurrentNode, 0)].myValueCounter;
	size_t linkID = 0;

	if (myNodes[aCurrentNode].myLinksIDs.Size() > 1)
	{
		for (size_t iLink = 0; iLink < myNodes[aCurrentNode].myLinksIDs.Size(); ++iLink)
		{
			Node::NodeValue tempValue = myNodes[GetOtherNode(aCurrentNode, iLink)].myValueCounter;
			if (bestValue > tempValue)
			{
				bestValue = tempValue;
				linkID = iLink;
			}
		}
	}

	aCurrentNode = bestValue.myNodeID;
	return linkID;
}


























/*

BAD STUFF DONT GO FUTHER

*/




















/*


STAAAAAAAAPPPPP


*/











































/*

CONTNINE AT YOUR OWN RISK

*/

































//if (aCurrentNode != aGoalNode)
//{
//	size_t pathCost;
//	size_t bestPathCost = SIZE_MAX;
//	size_t bestPathID;
//
//	for (size_t iLink = 0; iLink < myNodes[aCurrentNode].myLinksIDs.Size(); ++iLink)
//	{
//		if (myLinks[myNodes[aCurrentNode].myLinksIDs[iLink]].CheckIfHasBeenVisited() == false)
//		{
//			myLinks[myNodes[aCurrentNode].myLinksIDs[iLink]].Visit();
//			pathCost = Dijkstras(aPath, myLinks[myNodes[aCurrentNode].myLinksIDs[iLink]].GetOtherNode(aCurrentNode), aGoalNode);
//			if (pathCost < bestPathCost)
//			{
//				bestPathCost = pathCost;
//				bestPathID = iLink;
//			}
//		}
//	}
//
//	if (bestPathCost == SIZE_MAX)
//	{
//		return bestPathCost;
//	}
//	else
//	{
//		aPath.Add(bestPathID);
//		return bestPathCost + myLinks[myNodes[aCurrentNode].myLinksIDs[bestPathID]].GetCost();
//	}
//
//}
//else
//{
//	return 0;
//}