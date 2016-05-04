// DERPADERP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <BinaryTree/BinaryTree.h>
#include <NameSpaceAliases.h>


int _tmain(int argc, _TCHAR* argv[])
{

	CU::BinaryTree<int> treeeeeee;

	treeeeeee.InsertNode(13);
	treeeeeee.InsertNode(10);
	treeeeeee.InsertNode(25);
	treeeeeee.InsertNode(2);
	treeeeeee.InsertNode(12);
	treeeeeee.InsertNode(20);
	treeeeeee.InsertNode(29);
	treeeeeee.InsertNode(31);

	treeeeeee.InOrderTraverse();

	std::cout << " " << std::endl;
	treeeeeee.PostOrderTraverse();

	system("pause");

	return 0;
}


 