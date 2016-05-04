#pragma once

#include <GraphCluster/GraphCluster.h>
#include "GraphicalContent.h"


class Renderer;
class Randomizer;

class InteMartinHittaKakaCluster
{
public:
	InteMartinHittaKakaCluster();
	~InteMartinHittaKakaCluster();

	void Init();
	void AddNodesToRenderer(Renderer & aRendererToAddTo);
	void GenerateMap(const size_t nodeAmount, const Vector2f & aWorldConstraints);
	void DrawLinks(Renderer & aRenderer);

	void ShowPath(const CU::GrowingArray<size_t> & aPath, const size_t aStartNode);

	void FindPath();

private:
	void DrawLinksInNode(const size_t aNode, Renderer & aRenderer);
	void CreateARandomLink(const size_t aNode);
	
	Randomizer * myRandowmyzerx;
	CU::GraphCluster myCluster;
	CU::GrowingArray<GraphicalContent, size_t> myGraphicalNodes;
};