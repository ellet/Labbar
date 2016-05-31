#pragma once

#include "QuadTree/Circle.h"
#include "QuadTree/PointOfView.h"

struct OctoNode;

class OctoTree
{
public:
	OctoTree();
	~OctoTree();

	void Init(const CU::GrowingArray<CU::Vector3f> & aArrayOfPositions);

	void Update(const CU::Time & aTime);
	void Draw() const;

	void BuildTree(const CU::Vector3f & aAreaSize, const int aMax);
	OctoNode * CreateNode(const CU::Vector3f &aCenter, float aHalfWidth, float aLooseness, const int aCurrentDepth, OctoNode * aParent);

	void AddAllObjects();
	
	void UpdateObjectTreeLocation();

	void SetPointOfView(const CU::Vector2f & aPosition);
	void SetPointOfViewRotation(const CU::Vector3f & aPosition);

	void SetLooseNess(const float aDelta);
	CU::Vector4f GetColor(const int aDepth);

private:
	void CollisionCheckNode(OctoNode * aNode);
	void CollisionCheck();

	void AddObject(Circle * aCircle, OctoNode * aStartNode);
	unsigned short myMaxDepth;

	CU::Vector3f myArea;
	StaticSprite * myIncstructionSprite;

	OctoNode * myRootNode;
	CU::GrowingArray<Circle> myCircles;
	PointOfView myPointOfView;
};