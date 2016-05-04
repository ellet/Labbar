#pragma once

#include <GraphCluster/GraphCluster.h>
#include "GraphicalContent.h"
#include <sstream>


class Renderer;
class Randomizer;

class InteMartinHittaKakaCluster
{
public:
	InteMartinHittaKakaCluster();
	~InteMartinHittaKakaCluster();

	void Init();

	void Update();

	void AddNodesToRenderer(Renderer & aRendererToAddTo);
	void GenerateMap(const size_t nodeAmount, const Vector2f & aWorldConstraints);
	void DrawLinks(Renderer & aRenderer);
	void PrintNodeValues(Renderer & aRenderer);

	void UpdateNode(const size_t aCurrentNode);

	void ShowPath(const CU::GrowingArray<size_t> & aPath, const size_t aStartNode);

	void FindPath();

	bool SetStartNodeWithMouse(const Vector2f & aMouseClickedPosition);
	bool SetGoalNodeWithMouse(const Vector2f & aMouseClickedPosition);

	size_t ClickedNode(const Vector2f & aMouseClickedPosition);

	bool CheckIfDone()
	{
		return !myIsFindingPath;
	}

private:
	void CreateARandomLink(const size_t aNode);
	
	Randomizer * myRandowmyzerx;
	CU::GraphCluster myCluster;
	CU::GrowingArray<GraphicalContent, size_t> myGraphicalNodes;

	bool myIsFindingPath;
	size_t myPreviousUpdatedNode;

	size_t myStartNodeID;
	size_t myGoalNodeID;

	CU::GrowingArray<size_t>myPath;

	std::stringstream myNumberConverter;
};