#pragma once

#include "../GrowingArray/GrowingArray.h"
#include "../Heap/Heap.h"
#include "../Heap/PointerLesser.h"

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
					return (myValue < aRight.myValue);
				}

				bool operator>(const NodeValue& aRight)
				{
					return !(*this < aRight);
				}
				
				bool operator==(const size_t& aOther)
				{
					return (aOther == myValue);
				}

				size_t myValue;
				size_t myNodeID;
			};


			Node()
			{
				myLinksIDs.Init(2);
				ResetValueCounter();
				myIsInTheHeap = false;
			};

			void AddLink(const size_t aLinkID)
			{
				myLinksIDs.Add(aLinkID);
			};

			void SetValueCounter(const size_t aValue)
			{
				myValueCounter.myValue = aValue;
			}

			void ResetValueCounter()
			{
				myValueCounter.myValue = SIZE_MAX;
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

		private:
			CommonUtilities::GrowingArray<size_t, size_t> myLinksIDs;
			NodeValue myValueCounter;
			bool myIsInTheHeap;
		};

		class Link
		{
		public:
			Link()
			{}
			Link(const size_t & aFirstNode, const size_t & aSecondNode) : myFirstNodeID(aFirstNode), mySecondNodeID(aSecondNode)
			{
				myLinkCost = 1;
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

			size_t GetCost()
			{
				return myLinkCost;
			}

		private:
			bool myVisitedFlag;
			size_t myFirstNodeID;
			size_t mySecondNodeID;
			size_t myLinkCost;
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

		void ResetLinks();

		size_t GetOtherNode(const size_t aNodeID, const size_t aLinkID);

		void AddLinksToPathOptions(const size_t aNodeID);

		void Dijkstras(CommonUtilities::GrowingArray<size_t> & aPath, const size_t aCurrentNode, const size_t aGoalNode);

		size_t FindShortest(size_t& aCurrentNode);

	private:
		CommonUtilities::GrowingArray<Node, size_t> myNodes;
		CommonUtilities::GrowingArray<Link, size_t> myLinks;
		CommonUtilities::Heap<Node::NodeValue *, PointerLesser<Node::NodeValue *>> myPathOptions;
	};
}