#pragma once
#include "MapGenerationAlgorithm.h"

class RoomGenerator : public MapGenerationAlgorithm
{
public:
							RoomGenerator(EntityFactory& aEntityFactory, EnemyFactory& aEnemyFactory, Map& aMap, MapSetting& aMapSettings, MapFactory &aMapFactory);
							~RoomGenerator();

private:
	void					InitMap(const int aWidth, const int aHeight) override;
	void					CreateSpatialAreas() override;
	void					CreateExit() override;
	

	void					CreateCorridors(const int aRandomFactor);
	void					CreateRooms(const int aRoomCount, const int aMaxRoomWidth = 8,
								const int aMaxRoomHeight = 8, const int aMinRoomWidth = 1, const int aMinRoomHeight = 1);
	void					FurnishRooms();
	void					RemoveLonelyDoors(); // A door with only one wall
	void					RemoveRoomsMadeOfWalls();
	int						GetRoomIDFromTilePosition(const Vector2f& aTilePosition) const;
	bool					HasGeneratedEnoughRooms() const;
	bool					TilesAreWalls(const int aX, const int aY, const int aWidth, const int aHeight) const;

	CU::GrowingArray<Room>	myRooms;
};

