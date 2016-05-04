#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include "TreeNode.h"
#include <assert.h>


#ifndef SAFE_DELETE
#define SAFE_DELETE(aValue) delete aValue; aValue = nullptr;
#endif

template<class Type>
class BinaryTree
{
public:

	BinaryTree();
	~BinaryTree();

	inline const TreeNode<Type>* GetRootNode() const;

	inline void InsertNode(const TreeNode<Type>* aValueToInsert);
	inline void InsertNode(Type aValueToInsert);

	inline void DeleteNode(const TreeNode<Type>* aNode);
	inline void DeleteNode(Type aValue);

	inline TreeNode<Type>* Find(Type aValue);

	inline void PostOrderTraverse(void);
	inline void InOrderTraverse(void);

private:

	//helper functions and rootnode, these are used mainly for recursive use
	//starting from the rootnode and working their way down
	inline TreeNode<Type>* FindParent(TreeNode<Type>* aRoot, TreeNode<Type>* aChildNode);
	inline void InOrder(TreeNode<Type>* aNode);
	inline void PostOrder(TreeNode<Type>* aNode);

	inline void CycleToEnd(TreeNode<Type>* aPrev, TreeNode<Type>* aNodeToDelete, TreeNode<Type>* &aTmpToChange);

	inline void DeleteTreeFromNode(TreeNode<Type>* aNode);
	inline TreeNode<Type>* FindFromRoot(Type aValue, TreeNode<Type>* aNode);
	TreeNode<Type>* myRootNode;
};

template<typename Type>
BinaryTree<Type>::BinaryTree()
{
	myRootNode = nullptr;
}

template<typename Type>
BinaryTree<Type>::~BinaryTree()
{
	DeleteTreeFromNode(myRootNode);
}

template<typename Type>
const TreeNode<Type>* BinaryTree<Type>::GetRootNode()  const
{
	if(myRootNode != nullptr)
	{
		return myRootNode;
	}
	return nullptr;
}

template<typename Type>
TreeNode<Type>* BinaryTree<Type>::FindParent(TreeNode<Type>* aNode, TreeNode<Type>* aChildNode)
{
	if(aChildNode == myRootNode)
	{
		return nullptr;
	}

	if(aChildNode != nullptr)
	{
		if(aNode->myRightNode == aChildNode || aNode->myLeftNode == aChildNode)
		{
			return aNode;
		}

		if(aChildNode->myData > aNode->myData && aNode->myRightNode != nullptr)
		{
			aNode = FindParent(aNode->myRightNode, aChildNode);
		}
		else if(aChildNode->myData < aNode->myData && aNode->myLeftNode != nullptr)
		{
			aNode = FindParent(aNode->myLeftNode, aChildNode);
		}
		else
		{
			assert(aNode->myLeftNode != nullptr && "Trying to delete something that doesnt exist! line 94");
			assert(aNode->myRightNode != nullptr && "Trying to delete something that doesnt exist! line 95");
			return nullptr;
		}
	}
	return aNode;
}


template<typename Type>
void BinaryTree<Type>::InsertNode(const TreeNode<Type>* aValueToInsert)
{
	TreeNode<Type>* p		= myRootNode;
	TreeNode<Type>* prev	= nullptr;
	while (p != nullptr) 
	{
		prev = p;
		if (aValueToInsert->myData < p->myData)
		{
			p = p->myLeftNode;
		}
		else
		{
			p = p->myRightNode;
		}
	}
	if (myRootNode == nullptr)
	{
		myRootNode = aValueToInsert;
	}
	else if (aValueToInsert->myData < prev->myData)
	{
		prev->myLeftNode = aValueToInsert;
	}
	else
	{
		prev->myRightNode = aValueToInsert;
	}
}

template<typename Type>
void BinaryTree<Type>::InsertNode(Type aValueToInsert)
{
	TreeNode<Type>* node = new TreeNode<Type>;
	node->myData = aValueToInsert;
	InsertNode(node);
}

template<typename Type>
void BinaryTree<Type>::DeleteNode(const TreeNode<Type>* aNode)
{

	if(aNode == myRootNode && myRootNode->myLeftNode == nullptr && myRootNode->myRightNode == nullptr)
	{
		SAFE_DELETE(myRootNode);
		myRootNode = nullptr;
		return;
	}

	const TreeNode<Type>* tmp = aNode;
	const TreeNode<Type>* prev = FindParent(myRootNode, aNode);

	if (aNode != nullptr)
	{
		if(prev != nullptr)
		{
			if(aNode->myLeftNode == nullptr && aNode->myRightNode == nullptr)
			{
				if(prev->myLeftNode == aNode)
				{
					prev->myLeftNode = nullptr;
				}
				if(prev->myRightNode == aNode)
				{
					prev->myRightNode = nullptr;
				}
				SAFE_DELETE(aNode);
				return;
			}
		}

		if(aNode->myLeftNode == nullptr && aNode->myRightNode != nullptr)
		{
			if(prev != nullptr)
			{
				if(prev->myLeftNode == aNode)
				{
					prev->myLeftNode = aNode->myRightNode;
				}
				else if(prev->myRightNode == aNode)
				{
					prev->myRightNode = aNode->myRightNode;
				}
				SAFE_DELETE(aNode);
				return;
			}
			else
			{
				CycleToEnd(prev, aNode, tmp);
			}
		}
		else if(aNode->myRightNode == nullptr && aNode->myLeftNode != nullptr)
		{
			if(prev != nullptr)
			{
				if(prev->myLeftNode == aNode)
				{
					prev->myLeftNode = aNode->myLeftNode;
				}
				else if(prev->myRightNode == aNode)
				{
					prev->myRightNode = aNode->myLeftNode;
				}
				SAFE_DELETE(aNode);
				return;
			}
			else
			{
				CycleToEnd(prev, aNode, tmp);
			}
		}
		else
		{
			CycleToEnd(prev, aNode, tmp);
		}

		if(tmp->myLeftNode != nullptr)
		{
			prev = FindParent(myRootNode, tmp);
			if(prev->myRightNode == tmp)
			{
				prev->myRightNode = tmp->myLeftNode;
			}
		}

		SAFE_DELETE(tmp);
	}
}

template<typename Type>
void BinaryTree<Type>::DeleteNode(Type aValue)
{
	TreeNode<Type>* nodeToDelete = Find(aValue);
	DeleteNode(nodeToDelete);
}

template<typename Type>
inline void BinaryTree<Type>::CycleToEnd(TreeNode<Type>* aPrev, TreeNode<Type>* aNodeToDelete, TreeNode<Type>* &aTmpToChange)
{
	aTmpToChange = aNodeToDelete->myRightNode;
	while (aTmpToChange->myLeftNode != nullptr)
	{
		aTmpToChange = aTmpToChange->myLeftNode;
	}
	aNodeToDelete->myData = aTmpToChange->myData;

	aPrev = FindParent(myRootNode, aTmpToChange);
	if(aPrev->myLeftNode == aTmpToChange)
	{
		aPrev->myLeftNode = nullptr;
	}
	else if(aPrev->myRightNode == aTmpToChange)
	{
		aPrev->myRightNode = nullptr;
	}
}


template<typename Type>
TreeNode<Type>* BinaryTree<Type>::Find(Type aValue)
{
	if(myRootNode != nullptr)
	{
		return FindFromRoot(aValue, myRootNode);
	}
	return nullptr;
}

template<typename Type>
TreeNode<Type>* BinaryTree<Type>::FindFromRoot(Type aValue, TreeNode<Type>* aNode)
{
	if(aNode != nullptr)
	{
		if(aValue == aNode->myData)
		{
			return aNode;
		}
		if(aValue < aNode->myData)
		{
			return FindFromRoot(aValue, aNode->myLeftNode);
		}
		if(aValue > aNode->myData)
		{
			return FindFromRoot(aValue, aNode->myRightNode);
		}
	}
	return nullptr;
}

template<typename Type>
void BinaryTree<Type>::PostOrderTraverse(void)
{
	//this means go furthest to the left, followed by the right, and then visiting when
	//both have left + right as nullptr. LEFT-RIGHT-VISIT
	PostOrder(myRootNode);
}

template<typename Type>
void BinaryTree<Type>::InOrderTraverse(void)
{
	//this case means go furthest to the left, visit, right
	//LEFT-VISIT-RIGHT mode of traversing
	InOrder(myRootNode);
}

//helper function, to take the rootnode and use recursion to 
//check all the nodes and visit them in LVR order
template<typename Type>
inline void BinaryTree<Type>::InOrder(TreeNode<Type>* aNode)
{
	if (aNode != nullptr) 
	{
		InOrder(aNode->myLeftNode);
		std::cout << aNode->myData << std::endl;
		InOrder(aNode->myRightNode);
	}
}

template<typename Type>
inline void BinaryTree<Type>::PostOrder(TreeNode<Type>* aNode)
{
	if (aNode != nullptr) 
	{
		PostOrder(aNode->myLeftNode);
		PostOrder(aNode->myRightNode);
		std::cout << aNode->myData << std::endl;
	}
}

template<typename Type>
void BinaryTree<Type>::DeleteTreeFromNode(TreeNode<Type>* aNode)
{
	if(aNode != nullptr)
	{
		if(aNode->myLeftNode != nullptr)
		{
			DeleteTreeFromNode(aNode->myLeftNode);
		}
		if(aNode->myRightNode != nullptr)
		{
			DeleteTreeFromNode(aNode->myRightNode);
		}

		SAFE_DELETE(aNode);
	}
}

#endif