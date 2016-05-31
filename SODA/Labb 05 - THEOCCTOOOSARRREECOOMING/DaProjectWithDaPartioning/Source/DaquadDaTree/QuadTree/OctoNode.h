#pragma once



class Circle;

struct OctoNode
{
public:
	OctoNode()
	{
		myDwellers.Init(4);
		myParent = nullptr;
	}
	~OctoNode();

	


	OctoNode * myParent;
	Intersection3D::AABB myBox;

	CU::Vector4f myColor;

	CU::Vector3f myCenter;
	float myHalfWidth;

	static float ourLooseness;
	CU::StaticArray<OctoNode*, 8> myChildren;
	CU::GrowingArray<Circle*> myDwellers;
};