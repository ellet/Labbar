#ifndef TREE_NODE_H
#define TREE_NODE_H

template<class Type>
struct TreeNode
{
public:

	//default init everything to nullptr
	inline TreeNode();
	inline TreeNode(Type aData);

	TreeNode* myRightNode;
	TreeNode* myLeftNode;
	Type myData;

private:

};

template<typename Type>
TreeNode<Type>::TreeNode(Type aData) : myRightNode(nullptr),
		myLeftNode(nullptr)
{
	myRightNode = nullptr;
	myLeftNode = nullptr;
	myData = aData;
}

template<typename Type>
TreeNode<Type>::TreeNode() : myRightNode(nullptr),
		myLeftNode(nullptr), myData(NULL)
{
	myRightNode = nullptr;
	myLeftNode = nullptr;
	myData = NULL;
}


#endif