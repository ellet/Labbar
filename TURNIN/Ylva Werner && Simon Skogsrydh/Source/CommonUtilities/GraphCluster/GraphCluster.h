#pragma once

#include "../GrowingArray/GrowingArray.h"
#include "../Heap/Heap.h"
#include "../Heap/PointerLesser.h"
#include "../Vectors/vector2.h"

namespace CommonUtilities
{
	class GraphCluster
	{
	public:
		class Link;
		class Node
		{
		public:
			friend GraphCluster;

			struct NodeValue
			{
				bool operator<(const NodeValue& aRight)
				{
					return ((myDistanceToStart + myDistanceToGoal) < (aRight.myDistanceToStart + aRight.myDistanceToGoal));
				}

				bool operator>(const NodeValue& aRight)
				{
					return !(*this < aRight);
				}

				bool operator==(const float& aOther)
				{
					return (aOther == myDistanceToStart);
				}

				float myDistanceToStart;
				float myDistanceToGoal;
				size_t myNodeID;
			};


			Node()
			{
				myLinksIDs.Init(2);
				ResetValueCounter();
				myIsInTheHeap = false;
				myIsBlocked = false;
				myPosition = Vector2f::Zero;
				myValueCounter.myDistanceToGoal = FLT_MAX;
			};

			bool operator<(const Node& aRight)
			{
				return (myValueCounter < aRight.myValueCounter);
			}

			bool operator>(const Node& aRight)
			{
				return !(*this < aRight);
			}

			bool operator==(const float& aOther)
			{
				return (myValueCounter == aOther);
			}

			void AddLink(const size_t aLinkID)
			{
				myLinksIDs.Add(aLinkID);
			};

			void SetValueCounter(const float aValue)
			{
				myValueCounter.myDistanceToStart = aValue;
			}

			void ResetValueCounter()
			{
				myValueCounter.myDistanceToStart = FLT_MAX;
			}

			void SetToInHeap()
			{
				myIsInTheHeap = true;
			}

			void SetToNotInHeap()
			{
				myIsInTheHeap = false;
			}

			bool IsInHeap()
			{
				return myIsInTheHeap;
			}

			void SetID(const size_t aID)
			{
				myValueCounter.myNodeID = aID;
			}

			void SetBlock(const bool aIsBlocked)
			{
				myIsBlocked = aIsBlocked;
			}

			bool IsBlocked()
			{
				return myIsBlocked;
			}

			void SetPosition(const Vector2f aPosition)
			{
				myPosition = aPosition;
			}

			const Vector2f & GetPosition()
			{
				return myPosition;
			}

			void ResetNode()
			{
				ResetValueCounter();
				myIsInTheHeap = false;
			}

		private:
			CommonUtilities::GrowingArray<size_t, size_t> myLinksIDs;
			NodeValue myValueCounter;
			Vector2f myPosition;
			bool myIsInTheHeap;
			bool myIsBlocked;
		};

		class Link
		{
		public:
			Link()
			{}
			Link(const size_t & aFirstNode, const size_t & aSecondNode) : myFirstNodeID(aFirstNode), mySecondNodeID(aSecondNode)
			{
				myLinkCost = 1.f;
				myVisitedFlag = false;
			}

			size_t GetOtherNode(const size_t aNode)
			{
				if (aNode == myFirstNodeID)
				{
					return mySecondNodeID;
				}
				else
				{
					return myFirstNodeID;
				}
			}

			void Reset()
			{
				myVisitedFlag = false;
			}

			void Visit()
			{
				myVisitedFlag = true;
			}

			bool CheckIfHasBeenVisited()
			{
				return myVisitedFlag;
			}

			float GetCost()
			{
				return myLinkCost;
			}

			size_t GetFirstNodeID()
			{
				return myFirstNodeID;
			}

			size_t GetSecondNodeID()
			{
				return mySecondNodeID;
			}

		private:
			bool myVisitedFlag;
			size_t myFirstNodeID;
			size_t mySecondNodeID;
			float myLinkCost;
		};

	
		GraphCluster();
		~GraphCluster();

		size_t CreateNode();


		void ResetCluster()
		{
			myNodes.RemoveAll();
			myLinks.RemoveAll();
		}

		void CreateLink(const size_t aFirstNodeID, const size_t aSecondNodeID);

		size_t GetNodeLinkCount(const size_t aNodeID)
		{
			return myNodes[aNodeID].myLinksIDs.Size();
		}

		float GetNodeValue(const size_t aNodeID)
		{
			return myNodes[aNodeID].myValueCounter.myDistanceToStart;
		}

		void ResetLinks();

		size_t GetOtherNode(const size_t aNodeID, const size_t aLinkID);

		void SwitchNodeBlocked(const size_t aNodeID);

		void SetNodePosition(const size_t aNodeID, const Vector2f & aPosition);

		bool CheckNodeBlock(const size_t aNodeID);

		void StartAStar(const size_t aStartNode, const size_t aGoalIndex);

		bool AStar(CommonUtilities::GrowingArray<size_t> & aPath, size_t & aCurrentNode);

		void EndAStar(CommonUtilities::GrowingArray<size_t> & aPath);

		void EvaluateNode(Node & aNode);

		void EvaluateDistance(Node & aNode);

		float GetManhattanDistance(const Vector2f & aFirstPosition, const Vector2f & aSecondPosition);

		void AddNodeToHeap(Node * aNode);

		Node * GetNodeFromHeap();

		//void AddLinksToPathOptions(const size_t aNodeID);
		//void StartDjiktras(const size_t aStartNode);
		//bool Dijkstras(CommonUtilities::GrowingArray<size_t> & aPath, const size_t aGoalNode, size_t & aCurrentNode);
		//void EndDijkstras(CommonUtilities::GrowingArray<size_t> & aPath, const size_t aGoalNode);

		size_t FindShortest(size_t& aCurrentNode);

		CommonUtilities::GrowingArray<Link, size_t> myLinks;

	private:
		CommonUtilities::GrowingArray<Node, size_t> myNodes;

		CommonUtilities::GrowingArray<Node*, size_t> myClosedNodes;
		CommonUtilities::Heap<Node*, PointerLesser<Node*>> myOpenNodes;

		size_t myStartIndex;
		size_t myGoalIndex;

		//CommonUtilities::Heap<Node::NodeValue *, PointerLesser<Node::NodeValue *>> myPathOptions;
	};
}