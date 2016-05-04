#pragma once
#include "GrowingArray.h"
#include "Room.h"
#include "RoomTypeManager.h"

class Map;
class Player;
class Syncronizer;
class EntityFactory;
class MapFactory;
class EnemyFactory;
class MapSetting;

class MapGenerationAlgorithm
{
public:
						MapGenerationAlgorithm(EntityFactory& aEntityFactory, EnemyFactory& aEnemyFactory, Map& aMap, MapSetting& aMapSettings, MapFactory &aMapFactory);
	virtual				~MapGenerationAlgorithm();
	void				GenerateMap(Player &aPlayer);
	void				Init();

protected:
	virtual void		InitMap(const int aWidth, const int aHeight);

	virtual void		CreateSpatialAreas() = 0;
	virtual void		CreateEntrance();
	virtual void		CreateSpecials();
	virtual void		CreateExit();
	virtual void		CreateEnemies(const int aMaxCount, const int aMinCount);
	virtual void		CreateItems(const int aMaxCount, const int aMinCount);

	void				GenerateWallSides();
	void				RemoveTilesNotConnectedToEntrance();

	RoomTypeManager		myRoomTypeManager;
	MapSetting			&myMapSetting;
	Map					&myMap;
	MapFactory			&myMapFactory;

private:
	void				VisitTile(int aIndex, CU::GrowingArray<bool>& someVisitedTiles) const;
	bool				IndexOutOfBounds(const int aIndex) const;
	int					myStartTileIndex;
	EntityFactory		&myEntityFactory;
	EnemyFactory		&myEnemyFactory;
};

