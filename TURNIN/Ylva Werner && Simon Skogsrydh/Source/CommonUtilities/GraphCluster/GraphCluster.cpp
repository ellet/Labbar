#include "GraphCluster.h"


CommonUtilities::GraphCluster::GraphCluster()
{
	myNodes.Init(10);
	myClosedNodes.Init(10);
	myLinks.Init(20);
	myStartIndex = SIZE_MAX;
	myGoalIndex = SIZE_MAX;
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

void CommonUtilities::GraphCluster::SwitchNodeBlocked(const size_t aNodeID)
{
	bool oppositeOfNow = !myNodes[aNodeID].IsBlocked();
	myNodes[aNodeID].SetBlock(oppositeOfNow);
}
 
void CommonUtilities::GraphCluster::SetNodePosition(const size_t aNodeID, const Vector2f & aPosition)
{
	myNodes[aNodeID].SetPosition(aPosition);
}

bool CommonUtilities::GraphCluster::CheckNodeBlock(const size_t aNodeID)
{
	return myNodes[aNodeID].IsBlocked();
}

void CommonUtilities::GraphCluster::StartAStar(const size_t aStartNode, const size_t aGoalIndex)
{
	for (unsigned short iNode = 0; iNode < myNodes.Size(); ++iNode)
	{
		myNodes[iNode].ResetNode();
	}

	myGoalIndex = aGoalIndex;
	myNodes[aStartNode].myValueCounter.myDistanceToStart = 0.f;
	myOpenNodes.Enqueue(&myNodes[aStartNode]);
}

bool CommonUtilities::GraphCluster::AStar(CommonUtilities::GrowingArray<size_t> & aPath, size_t & aCurrentNode)
{
	if (myOpenNodes.IsEmpty() == true)
	{
		aCurrentNode = myGoalIndex;
		return false;
	}
	Node * node = GetNodeFromHeap();

	aCurrentNode = node->myValueCounter.myNodeID;

	if (node == &myNodes[myGoalIndex])
	{
		EvaluateNode(*node);
		EndAStar(aPath);
		myOpenNodes.RemoveAll();
		myClosedNodes.RemoveAll();
	}
	else
	{
		EvaluateNode(*node);
	}

	return true;
}

void CommonUtilities::GraphCluster::EndAStar(CommonUtilities::GrowingArray<size_t> & aPath)
{
	size_t currentNode = myGoalIndex;
	Node *tempNode = &myNodes[currentNode];
	do
	{
		aPath.Add(FindShortest(currentNode));
		tempNode = &myNodes[currentNode];

		if (aPath.Size() > 9)
		{
			int apa = 10;
			++apa;
		}

	} while (myNodes[currentNode].myValueCounter.myDistanceToStart != 0.f);
}

void CommonUtilities::GraphCluster::EvaluateNode(Node & aNode)
{
	for (size_t iLink = 0; iLink < aNode.myLinksIDs.Size(); ++iLink)
	{
		Node * neighbour = &myNodes[myLinks[aNode.myLinksIDs[iLink]].GetOtherNode(aNode.myValueCounter.myNodeID)];
		if (neighbour->IsBlocked() == false)
		{
			if (myClosedNodes.Find(neighbour) != SIZE_MAX)
			{
				continue;
			}
			float gValue = aNode.myValueCounter.myDistanceToStart + myLinks[aNode.myLinksIDs[iLink]].GetCost();
			if (gValue < neighbour->myValueCounter.myDistanceToStart && neighbour->myIsInTheHeap == true)
			{
				neighbour->myValueCounter.myDistanceToStart = gValue;
			}
			else if (neighbour->myIsInTheHeap == false)
			{
				neighbour->myValueCounter.myDistanceToStart = gValue;
				EvaluateDistance(*neighbour);
				AddNodeToHeap(neighbour);
			}
		}
	}
	myClosedNodes.Add(&aNode);
}

void CommonUtilities::GraphCluster::EvaluateDistance(Node & aNode)
{
	aNode.myValueCounter.myDistanceToGoal = GetManhattanDistance(myNodes[myGoalIndex].GetPosition() , aNode.GetPosition());
}

float CommonUtilities::GraphCluster::GetManhattanDistance(const Vector2f & aFirstPosition, const Vector2f & aSecondPosition)
{
	return (abs(aSecondPosition.x - aFirstPosition.x) + abs(aSecondPosition.y - aFirstPosition.y));
}

void CommonUtilities::GraphCluster::AddNodeToHeap(Node * aNode)
{
	aNode->myIsInTheHeap = true;
	myOpenNodes.Enqueue(aNode);
}

CommonUtilities::GraphCluster::Node * CommonUtilities::GraphCluster::GetNodeFromHeap()
{
	Node * tempNode = myOpenNodes.Dequeue();
	tempNode->myIsInTheHeap = false;
	return tempNode;
}

//void CommonUtilities::GraphCluster::AddLinksToPathOptions(const size_t aNodeID)
//{
//	for (size_t iLink = 0; iLink < myNodes[aNodeID].myLinksIDs.Size(); ++iLink)
//	{
//		Node::NodeValue & value = myNodes[GetOtherNode(aNodeID, iLink)].myValueCounter;
//		size_t cost = myNodes[aNodeID].myValueCounter.myValue + myLinks[myNodes[aNodeID].myLinksIDs[iLink]].GetCost();
//		if (cost < value.myValue)
//		{
//			if (myNodes[GetOtherNode(aNodeID, iLink)].IsBlocked() == false)
//			{
//				value.myValue = cost;
//				if (myNodes[GetOtherNode(aNodeID, iLink)].IsInHeap() == false)
//				{
//					myNodes[GetOtherNode(aNodeID, iLink)].SetToInHeap();
//					myPathOptions.Enqueue(&value);
//				}
//				else
//				{
//					myPathOptions.Resort();
//				}
//			}
//		}
//		
//	}
//}


//void CommonUtilities::GraphCluster::StartDjiktras(const size_t aStartNode)
//{
//	for (size_t iNode = 0; iNode < myNodes.Size(); ++iNode)
//	{
//		myNodes[iNode].ResetValueCounter();
//	}
//
//	myNodes[aStartNode].SetValueCounter(0);
//	AddLinksToPathOptions(aStartNode);
//}
//
//bool CommonUtilities::GraphCluster::Dijkstras(CommonUtilities::GrowingArray<size_t> & aPath, const size_t aGoalNode, size_t & aCurrentNode)
//{
//	size_t currentNode = myPathOptions.Dequeue()->myNodeID;
//	
//	aCurrentNode = currentNode;
//	myNodes[currentNode].SetToNotInHeap();
//	//if (myNodes[currentNode].IsBlocked() == false)
//	//{
//		AddLinksToPathOptions(currentNode);
//	//}
//
//	if (myPathOptions.IsEmpty() == true)
//	{
//		if (myNodes[aGoalNode].myValueCounter.myValue != SIZE_MAX)
//		{
//			EndDijkstras(aPath, aGoalNode);
//		}
//		return false;
//	}
//	
//	return true;
//}
//
//void CommonUtilities::GraphCluster::EndDijkstras(CommonUtilities::GrowingArray<size_t> & aPath, const size_t aGoalNode)
//{
//	size_t currentPosition = aGoalNode;
//	do
//	{
//		aPath.Add(FindShortest(currentPosition));
//
//	} while (myNodes[currentPosition].myValueCounter.myValue != 0);
//}

size_t CommonUtilities::GraphCluster::FindShortest(size_t& aCurrentNode)
{
	Node::NodeValue bestValue = myNodes[GetOtherNode(aCurrentNode, 0)].myValueCounter;
	size_t linkID = 0;

	if (myNodes[aCurrentNode].myLinksIDs.Size() > 1)
	{
		for (size_t iLink = 0; iLink < myNodes[aCurrentNode].myLinksIDs.Size(); ++iLink)
		{
			Node::NodeValue tempValue = myNodes[GetOtherNode(aCurrentNode, iLink)].myValueCounter;
			
			if (bestValue.myDistanceToStart > tempValue.myDistanceToStart)
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

