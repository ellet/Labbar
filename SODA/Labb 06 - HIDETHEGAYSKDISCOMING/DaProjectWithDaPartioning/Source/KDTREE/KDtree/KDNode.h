#pragma once
#include "KDtree/Circle.h"
#include <CU/GrowingArray/GrowingArray.h>


struct KDNode
{
	KDNode()
	{
		myLeftNode = nullptr;
		myRightNode = nullptr;
		myObjects.Init(1);
	}

	CU::Vector4f myREKT;
	CU::GrowingArray<Circle*> myObjects;
	Intersection2D::LineSegment2D mySplit;
	
	KDNode * myLeftNode;
	KDNode * myRightNode;
};