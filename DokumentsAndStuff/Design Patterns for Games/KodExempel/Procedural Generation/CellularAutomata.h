#pragma once
#include "MapGenerationAlgorithm.h"

class CellularAutomata : public MapGenerationAlgorithm
{
public:
						CellularAutomata(EntityFactory& aEntityFactory, EnemyFactory& aEnemyFactory, Map& aMap, MapSetting& aMapSettings, MapFactory &aMapFactory);
						~CellularAutomata();

private:
	void				CreateSpatialAreas() override;
	void				CreateCaves();
	void				RandomizeWalls();
	void				SmoothMap(const int aWallLimit, const int aFloorLimit, const int aSize = 1);
	int					GetSurroundingWallCount(const int aX, const int aY, const int aSize = 1);
};

