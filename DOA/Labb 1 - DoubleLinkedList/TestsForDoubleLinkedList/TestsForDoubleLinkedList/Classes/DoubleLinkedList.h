#pragma once
#include <assert.h>

namespace CommonUtilities
{

	template <typename T>
	class DoubleLinkedList
	{
	public: 
		struct Node
		{
		public:
			template <typename T>
			Node(T & aDataPointer)
			{
				myNext = nullptr;
				myPrev = nullptr;
				myData = aDataPointer;
			}

			Node* myNext;
			Node* myPrev;
			T myData;
		};

		DoubleLinkedList();
		~DoubleLinkedList();

		Node* GetFirstNode(); // Returnerar nullptr om ingen nod existerar

		inline Node* GetLastNode(); // Returnerar nullptr om ingen nod existerar

		inline void InsertNodeBeforeNode(Node* aNode, Node* aNodeToInsert);

		inline void InsertNodeAfterNode(Node* aNode, Node* aNodeToInsert);

		inline void InsertNodeSorted(Node* aNodeToInsert); // störst först

		inline void InsertNodeSorted(const T & aValueToInsert); // störst först

		inline void DeleteNode(const T & aValueToDelete); // Assertar om noden inte finns

		inline void DeleteNode(Node* aNodeToDelete); // Assertar om noden inte finns

		inline Node* Find(const T & aValue);


	private:
		Node * myFirstNode;
		Node * myLastNode;
	};

	template <typename T>
	CommonUtilities::DoubleLinkedList<T>::DoubleLinkedList()
	{
		myFirstNode = nullptr;
		myLastNode = nullptr;
	}

	template <typename T>
	CommonUtilities::DoubleLinkedList<T>::~DoubleLinkedList()
	{

	}

	template <typename T>
	typename DoubleLinkedList<T>::Node* CommonUtilities::DoubleLinkedList<T>::GetFirstNode()
	{
		return myFirstNode;
	}

	template <typename T>
	typename DoubleLinkedList<T>::Node* CommonUtilities::DoubleLinkedList<T>::GetLastNode()
	{
		return myLastNode;
	}

	
	template <typename T>
	void CommonUtilities::DoubleLinkedList<T>::InsertNodeBeforeNode(Node* aNode, Node* aNodeToInsert)
	{
		if (aNode == nullptr || aNode == myFirstNode)
		{
			aNodeToInsert->myNext = myFirstNode;
			aNodeToInsert->myPrev = nullptr;

			if (aNode != nullptr)
			{
				aNode->myPrev = aNodeToInsert;
			}
			else
			{
				myLastNode = aNodeToInsert;
			}

			myFirstNode = aNodeToInsert;
		}
		else
		{
			aNodeToInsert->myNext = aNode;
			aNodeToInsert->myPrev = aNode->myPrev;
			aNodeToInsert->myPrev->myNext = aNodeToInsert;

			aNode->myPrev = aNodeToInsert;
		}
	}

	
	template <typename T>
	void CommonUtilities::DoubleLinkedList<T>::InsertNodeAfterNode(Node* aNode, Node* aNodeToInsert)
	{
		if (aNode == nullptr || aNode == myLastNode)
		{
			aNodeToInsert->myNext = nullptr;

			if (aNode != nullptr)
			{
				aNodeToInsert->myPrev = aNode;
				aNode->myNext = aNodeToInsert;
			}
			else
			{
				myFirstNode = aNodeToInsert;
			}

			myLastNode = aNodeToInsert;
		}
		else
		{
			aNodeToInsert->myPrev = aNode;
			aNodeToInsert->myNext = aNode->myNext;
			aNodeToInsert->myNext->myPrev = aNodeToInsert;

			aNode->myNext = aNodeToInsert;
		}
	}

	
	template <typename T>
	void CommonUtilities::DoubleLinkedList<T>::InsertNodeSorted(Node* aNodeToInsert)
	{
		Node * tmpCurrentNode = myFirstNode;
		while (tmpCurrentNode != nullptr)
		{
			if (tmpCurrentNode->myData < aNodeToInsert->myData)
			{
				InsertNodeBeforeNode(tmpCurrentNode, aNodeToInsert);
				return;
			}
			tmpCurrentNode = tmpCurrentNode->myNext;
		}

		InsertNodeAfterNode(myLastNode, aNodeToInsert);
	}


	
	template <typename T>
	void CommonUtilities::DoubleLinkedList<T>::InsertNodeSorted(const T & aValueToInsert)
	{
		InsertNodeSorted(new Node(*new T(aValueToInsert)));
	}


	template <typename T>
	void CommonUtilities::DoubleLinkedList<T>::DeleteNode(const T & aValueToDelete)
	{
		Node * tmpNodeToDelete = Find(aValueToDelete);
		assert(tmpNodeToDelete != nullptr && "Tried to Delete a node that does not exist");
		


		if (tmpNodeToDelete != myFirstNode)
		{
			tmpNodeToDelete->myPrev->myNext = tmpNodeToDelete->myNext;
		}
		else
		{
			myFirstNode = tmpNodeToDelete->myNext;
		}

		if (tmpNodeToDelete != myLastNode)
		{
			tmpNodeToDelete->myNext->myPrev = tmpNodeToDelete->myPrev;
		}
		else
		{
			myLastNode = tmpNodeToDelete->myPrev;
		}

		delete tmpNodeToDelete;
	}


	template <typename T>
	void CommonUtilities::DoubleLinkedList<T>::DeleteNode(Node* aNodeToDelete)
	{
		assert(aNodeToDelete != nullptr && (Find(aNodeToDelete->myData) != nullptr) && "Tried to Delete a node that does not exist");

		if (aNodeToDelete != myFirstNode)
		{
			aNodeToDelete->myPrev->myNext = aNodeToDelete->myNext;
		}
		else
		{
			myFirstNode = aNodeToDelete->myNext;
		}

		if (aNodeToDelete != myLastNode)
		{
			aNodeToDelete->myNext->myPrev = aNodeToDelete->myPrev;
		}
		else
		{
			myLastNode = aNodeToDelete->myPrev;
		}
		
	}
	
	
	template <typename T>
	typename DoubleLinkedList<T>::Node* CommonUtilities::DoubleLinkedList<T>::Find(const T & aValue)
	{
		Node * tmpCurrentNode = myFirstNode;

		while (tmpCurrentNode != nullptr)
		{
			if (tmpCurrentNode->myData == aValue)
			{
				return tmpCurrentNode;
			}
			tmpCurrentNode = tmpCurrentNode->myNext;
		}

		return nullptr;
	}
}