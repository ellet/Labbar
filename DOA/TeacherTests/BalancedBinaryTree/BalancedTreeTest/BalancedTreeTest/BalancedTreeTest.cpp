// BalancedTreeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


/*
#include "BinaryTree.h"
/*/
#include "binary_tree.h"
//*/

namespace CommonUtilities
{
}

using namespace CommonUtilities;


int _tmain(int argc, _TCHAR* argv[])
{
	BinaryTree<int> tree;

	for (int i = 0; i < 13; ++i)
		tree.InsertNode(rand()%100);

	tree.DSW_Balance();

	system("pause");

	return 0;
}

