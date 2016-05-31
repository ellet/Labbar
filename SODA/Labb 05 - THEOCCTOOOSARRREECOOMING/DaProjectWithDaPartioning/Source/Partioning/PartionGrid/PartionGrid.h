#pragma once

#include "PartionGrid/Circle.h"
#include "PartionGrid/PointOfView.h"
#include "PartionGrid/Tile.h"

class PartionGrid
{
public:
	PartionGrid();
	~PartionGrid();

	void Init(const CU::GrowingArray<CU::Vector2f> & aCirclePositions);
	void Update();
	void Draw() const;

	void SetPointOfViewPosition(const CU::Vector2f & aPosition);

private:
	void CollisionTest();
	void AssignCirclesToTiles();
	bool RaySight(const CU::Vector2f & aCirclePosition, const CU::Vector2f & aPoVPosition);
	bool CircleIsVisible(Circle & aCircle, const CU::Vector2f & aPoVPosition);
	CU::GridArray<Tile> myTiles;
	CU::GrowingArray<Circle> myCircles;
	PointOfView myPointOfView;
};