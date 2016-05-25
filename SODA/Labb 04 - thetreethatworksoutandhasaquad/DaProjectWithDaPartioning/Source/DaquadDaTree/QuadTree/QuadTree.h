#pragma once

#include "QuadTree/Circle.h"
#include "QuadTree/PointOfView.h"

struct QuadNode;

class QuadTree
{
public:
	QuadTree();
	~QuadTree();

	void Init(const CU::GrowingArray<CU::Vector2f> & aArrayOfPositions);

	void Update(const CU::Time & aTime);
	void Draw() const;


	void BuildTree(const CU::Vector2f & aAreaSize, const int aMax);
	QuadNode * CreateNode(const CU::Vector2f &aCenter, float aHalfWidth, const int aCurrentDepth, QuadNode * aParent);

	void AddAllObjects();
	
	void UpdateObjectTreeLocation();

	void SetPointOfView(const CU::Vector2f & aPosition);
	void SetPointOfViewRotation(const CU::Vector2f & aPosition);

private:
	bool CircleRayCollisionCheck(const Circle & aCircle);

	void CollisionCheckNode(QuadNode * aNode);
	void CollisionCheck();

	void AddObject(Circle * aCircle, QuadNode * aStartNode);
	unsigned short myMaxDepth;

	QuadNode * myRootNode;
	CU::GrowingArray<Circle> myCircles;
	PointOfView myPointOfView;
};