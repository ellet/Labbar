#pragma once
//#include "DLDebug/DL_Debug.h"
#include <ostream>
#include <iostream>
#include <functional>
#include <assert.h>

#define DL_ASSERT(Statment, String) assert(Statment);

namespace CommonUtilities
{
	template<typename T>
	class BinaryTree;


	template <typename T>
	class TreeNode
	{
		friend BinaryTree < T > ;
	public:
		TreeNode(const T & aValueToHold)
		{
			myRight = nullptr;
			myLeft = nullptr;
			myData = aValueToHold;
		}

		const T & GetData() const
		{
			return myData;
		}

		T & GetData()
		{
			return myData;
		}

		const TreeNode * GetLeftChild() const
		{
			return myLeft;
		}

		const TreeNode * GetRightChild() const
		{
			return myRight;
		}

	private:
		TreeNode * myLeft;
		TreeNode * myRight;

		

		T myData;
	};

	template <typename T>
	class BinaryTree
	{
	public:
		BinaryTree();
		~BinaryTree();

		TreeNode<T>* GetRootNode() const;

		TreeNode<T>* Find(const T & aValue);

		void InsertNode(TreeNode<T>* aValueToInsert);
		void InsertNode(const T & aValueToInsert);

		void DeleteNode(TreeNode<T> * aNode);
		void DeleteNode(const T & aValue);

		void DSW_Balance();

		void InOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode);
		void InOrderTraverseFunction(const std::function<void(const T&)> & aFunction, const TreeNode<T> & aNode) const;
		void InOrderTraverse(void);

		void PostOrderTraverseFunction(const std::function<void(const T&)> & aFunction, const TreeNode<T> & aNode) const;
		void PostOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode);
		void PostOrderTraverse(void);

		int GetSize() const;

		void ChangeToBackBone();

	private:
		void BalanceTree();

		void RotateRight(TreeNode<T> * aGrandParent, TreeNode<T> * aParent, TreeNode<T> * aChild);
		void RotateLeft(TreeNode<T> * aGrandParent, TreeNode<T> * aParent, TreeNode<T> * aChild);

		void AddNode(TreeNode<T> & aNodeToAdd, TreeNode<T> & aNodeToCheck);
		TreeNode<T> * FindLocal(const T & aValueToFind, TreeNode<T> * aNodeToCheck);

		void DeleteNodeLocal(TreeNode<T>* & aParent, TreeNode<T> & aNodeToDelete);

		void IncreaseNumber(int & aNumber, const T & aMeh) const;
		void OutputNodeToStream(std::ostream & aStreamToAddTo, const T & aNodeData);

		TreeNode<T> * myFirstNode;
	};

	template <typename T>
	void CommonUtilities::BinaryTree<T>::PostOrderTraverseFunction(const std::function<void(const T&)> & aFunction, const TreeNode<T> & aNode) const
	{
		if (aNode.myLeft != nullptr)
		{
			PostOrderTraverseFunction(aFunction, *aNode.myLeft);
		}

		if (aNode.myRight != nullptr)
		{
			PostOrderTraverseFunction(aFunction, *aNode.myRight);
		}

		aFunction(aNode.myData);
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::OutputNodeToStream(std::ostream & aStreamToAddTo, const T & aNodeData)
	{
		aStreamToAddTo << aNodeData << std::endl;
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::IncreaseNumber(int & aNumber, const T & aMeh) const
	{
		++aNumber;
	}

	template <typename T>
	int CommonUtilities::BinaryTree<T>::GetSize() const
	{
		int numberOfNodes = 0;
		
		using std::placeholders::_1;

		InOrderTraverseFunction(std::bind(&BinaryTree::IncreaseNumber, this, std::ref(numberOfNodes), _1), *myFirstNode);

		return numberOfNodes;
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::RotateRight(TreeNode<T> * aGrandParent, TreeNode<T> * aParent, TreeNode<T> * aChild)
	{
		if (aGrandParent == nullptr)
		{
			myFirstNode = aChild;
		}
		else
		{
			aGrandParent->myRight = aChild;
		}
		aParent->myLeft = aChild->myRight;
		aChild->myRight = aParent;
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::RotateLeft(TreeNode<T> * aGrandParent, TreeNode<T> * aParent, TreeNode<T> * aChild)
	{
		if (aGrandParent == nullptr)
		{
			myFirstNode = aChild;
		}
		else
		{
			aGrandParent->myRight = aChild;
		}
		aParent->myRight = aChild->myLeft;
		aChild->myLeft = aParent;
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::ChangeToBackBone()
	{
		TreeNode<T>* tempGrandParent = nullptr;
		TreeNode<T>* tempTreeNode = myFirstNode;

		while (tempTreeNode != nullptr)
		{
			if (tempTreeNode->myLeft != nullptr)
			{
				RotateRight(tempGrandParent, tempTreeNode, tempTreeNode->myLeft);
				if (tempGrandParent == nullptr)
				{
					tempTreeNode = myFirstNode;
				}
				else
				{
					tempTreeNode = tempGrandParent->myRight;
				}
			}
			else
			{
				tempGrandParent = tempTreeNode;
				tempTreeNode = tempTreeNode->myRight;
			}
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::BalanceTree()
	{
		int size = GetSize();
		double stopPoint = std::pow(2, (floor(log2(size + 1)))) - 1;

		TreeNode<T> * grandParent = nullptr;
		TreeNode<T> * parent = myFirstNode;
		TreeNode<T> * child = parent->myRight;

		for (int iRotations = 0; iRotations < (size - static_cast<int>(stopPoint)); ++iRotations)
		{
			RotateLeft(grandParent, parent, child);
			grandParent = child;
			parent = child->myRight;
			child = parent->myRight;
		}

		while (stopPoint > 1.f)
		{
			stopPoint /= 2.f;

			grandParent = nullptr;
			parent = myFirstNode;
			child = parent->myRight;

			for (int iRotations = 0; iRotations < static_cast<int>(stopPoint); ++iRotations)
			{
				RotateLeft(grandParent, parent, child);
				grandParent = child;
				parent = child->myRight;
				child = parent->myRight;
			}
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DSW_Balance()
	{
		ChangeToBackBone();
		BalanceTree();
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::PostOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode)
	{
		using std::placeholders::_1;

		PostOrderTraverseFunction(std::bind(&BinaryTree::OutputNodeToStream, this, std::ref(aStreamToAddTo), _1), *myFirstNode);
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::PostOrderTraverse(void)
	{
		if (myFirstNode != nullptr)
		{
			PostOrderTraverseStream(std::cout, *myFirstNode);
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InOrderTraverseStream(std::ostream & aStreamToAddTo, const TreeNode<T> & aNode)
	{
		using std::placeholders::_1;

		InOrderTraverseFunction(std::bind(&BinaryTree::OutputNodeToStream, this, std::ref(aStreamToAddTo), _1), *myFirstNode);
	}


	template <typename T>
	void CommonUtilities::BinaryTree<T>::InOrderTraverseFunction(const std::function<void(const T&)> & aFunction, const TreeNode<T> & aNode) const
	{
		if (aNode.myLeft != nullptr)
		{
			InOrderTraverseFunction(aFunction, *aNode.myLeft);
		}

		aFunction(aNode.myData);

		if (aNode.myRight != nullptr)
		{
			InOrderTraverseFunction(aFunction, *aNode.myRight);
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InOrderTraverse(void)
	{
		if (myFirstNode != nullptr)
		{
			InOrderTraverseStream(std::cout, *myFirstNode);
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DeleteNode(const T & aValue)
	{
		DeleteNode(Find(aValue));
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DeleteNodeLocal(TreeNode<T>* & aParent, TreeNode<T> & aNodeToDelete)
	{

		if (aNodeToDelete.myLeft == nullptr)
		{
			aParent = aNodeToDelete.myRight;
		}
		else if (aNodeToDelete.myRight == nullptr)
		{
			aParent = aNodeToDelete.myLeft;
		}
		else
		{
			TreeNode<T> * previous = &aNodeToDelete;
			TreeNode<T> * temp = aNodeToDelete.myLeft;

			while (temp->myRight != nullptr)
			{
				previous = temp;
				temp = temp->myRight;
			}

			aNodeToDelete.myData = temp->GetData();

			if (previous == &aNodeToDelete)
			{
				previous->myLeft = temp->myLeft;
			}
			else
			{
				previous->myRight = temp->myLeft;
			}
			delete temp;
			temp = nullptr;
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::DeleteNode(TreeNode<T> * aNode)
	{
		DL_ASSERT(myFirstNode != nullptr, "Trying to delete a node in an empty tree!");
		DL_ASSERT(aNode != nullptr, "Trying to delete a node that doesn't exist!");

		TreeNode<T> * toCheck = myFirstNode;

		if (aNode->GetData() == toCheck->GetData())
		{
			DeleteNodeLocal(myFirstNode, *aNode);
			return;
		}

		while (toCheck->myLeft != nullptr || toCheck->myRight != nullptr)
		{
			if (toCheck->myLeft != nullptr)
			{
				if (aNode->GetData() == toCheck->myLeft->GetData())
				{
					DeleteNodeLocal(toCheck->myLeft, *aNode);
					return;
				}
			}
			if (toCheck->myRight != nullptr)
			{
				if (aNode->GetData() == toCheck->myRight->GetData())
				{
					DeleteNodeLocal(toCheck->myRight, *aNode);
					return;
				}
			}
			if (aNode->GetData() < toCheck->GetData())
			{
				toCheck = toCheck->myLeft;
			}
			else
			{
				toCheck = toCheck->myRight;
			}
		}
		DL_ASSERT(Find(aNode->GetData()) == nullptr, "Trying to delete a node that doesn't exist");
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InsertNode(const T & aValueToInsert)
	{
		InsertNode(new TreeNode<T>(aValueToInsert));
	}

	template <typename T>
	TreeNode<T> * CommonUtilities::BinaryTree<T>::FindLocal(const T & aValueToFind, TreeNode<T> * aNodeToCheck)
	{
		if (aNodeToCheck == nullptr)
		{
			return aNodeToCheck;
		}

		if (aValueToFind == aNodeToCheck->GetData())
		{
			return aNodeToCheck;
		}
		else if (aValueToFind < aNodeToCheck->GetData())
		{
			return FindLocal(aValueToFind, aNodeToCheck->myLeft);
		}
		else
		{
			return FindLocal(aValueToFind, aNodeToCheck->myRight);
		}
	}

	template <typename T>
	TreeNode<T>* CommonUtilities::BinaryTree<T>::Find(const T & aValue)
	{
		return FindLocal(aValue, myFirstNode);
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::AddNode(TreeNode<T> & aNodeToAdd, TreeNode<T> & aNodeToCheck)
	{
		if (aNodeToAdd.GetData() < aNodeToCheck.GetData())
		{
			if (aNodeToCheck.myLeft == nullptr)
			{
				aNodeToCheck.myLeft = &aNodeToAdd;
			}
			else
			{
				AddNode(aNodeToAdd, *aNodeToCheck.myLeft);
			}
		}
		else
		{
			if (aNodeToCheck.myRight == nullptr)
			{
				aNodeToCheck.myRight = &aNodeToAdd;
			}
			else
			{
				AddNode(aNodeToAdd, *aNodeToCheck.myRight);
			}
		}
	}

	template <typename T>
	void CommonUtilities::BinaryTree<T>::InsertNode(TreeNode<T>* aValueToInsert)
	{
		DL_ASSERT(aValueToInsert != nullptr, "BinaryTree InsertNode trying to insert nullptr");

		if (myFirstNode != nullptr)
		{
			AddNode(*aValueToInsert, *myFirstNode);
		}
		else
		{
			myFirstNode = aValueToInsert;
		}
	}

	template <typename T>
	TreeNode<T>* CommonUtilities::BinaryTree<T>::GetRootNode() const
	{
		return myFirstNode;
	}

	template <typename T>
	CommonUtilities::BinaryTree<T>::BinaryTree()
	{
		myFirstNode = nullptr;
	}

	template <typename T>
	CommonUtilities::BinaryTree<T>::~BinaryTree()
	{

	}

};