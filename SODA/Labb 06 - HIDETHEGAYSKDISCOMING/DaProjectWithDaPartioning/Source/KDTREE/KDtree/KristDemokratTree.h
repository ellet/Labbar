#pragma once

#include "KDtree/Circle.h"
#include "KDtree/PointOfView.h"
#include "KDtree/KDNode.h"

class KDTree
{
public:
	KDTree();
	~KDTree();
	void Init(const CU::GrowingArray<CU::Vector2f> & aArrayOfObjectPositions, const CU::GrowingArray<float> & aArrayOfRaidua);
	void BuildTree(const CU::Vector2f & aTreeArea, int aMaxDepth);

	void SetupPointOfView(const CU::Vector2f & aStartPoint, const CU::Vector2f & aEndPoint);

	void Update(const CU::Time & aTime);
	void Draw() const;

private:
	void CullingPointOfView();
	KDNode* BuildTreeNode(const CU::GrowingArray<Circle*> & aRelevantCircles, const CU::Vector4f & aNodeREKT, const int aCurrentDepth, bool aIsX);

	void DrawNodes(const KDNode & aNodeToDraw) const;

	void DeleteNodes(const KDNode & aNodeToDraw);

	int myMaxDepth;

	KDNode* myRootNode;

	CU::GrowingArray<KDNode> myNodes;
	CU::GrowingArray<Circle> myCircles;
	PointOfView myPointOfView;
};