#pragma once



class Circle;


struct QuadNode
{
public:
	QuadNode()
	{
		myDwellers.Init(4);
		myParent = nullptr;
	}
	~QuadNode();

	QuadNode * myParent;
	Intersection2D::AABB2D myBox;

	CU::Vector2f myCenter;
	float myHalfWidth;
	CU::StaticArray<QuadNode*, 4> myChildren;
	CU::GrowingArray<Circle*> myDwellers;
};