#include "stdafx.h"
#include "RoomGenerator.h"
#include "Map.h"
#include "CorridorDigger.h"
#include "Backdrop.h"
#include "BackDropType.h"
#include "MapSetting.h"
#include "MapFactory.h"

RoomGenerator::RoomGenerator(EntityFactory& aEntityFactory, EnemyFactory& aEnemyFactory, Map& aMap, MapSetting& aMapSettings, MapFactory &aMapFactory) :
	MapGenerationAlgorithm(aEntityFactory, aEnemyFactory, aMap, aMapSettings, aMapFactory)
{
}

RoomGenerator::~RoomGenerator()
{
}

void RoomGenerator::CreateCorridors(const int aRandomFactor)
{
	if (myRooms.Size() > 1)
	{
		for (int i = 0; i < myRooms.Size(); ++i)
		{
			int exits = (rand() % 3) + 1;
			for (int exitCount = 0; exitCount < exits; ++exitCount)
			{
				CorridorDigger digger;
				digger.StartDigging(myRooms[i], myMap, myMapFactory, aRandomFactor);
			}
		}
	}
}

void RoomGenerator::RemoveLonelyDoors()
{
	for (int roomIndex = 0; roomIndex < myRooms.Size(); ++roomIndex)
	{
		for (int doorIndex = myRooms[roomIndex].myDoorLocations.Size() - 1; doorIndex >= 0; --doorIndex)
		{
			int doorMapIndex = myRooms[roomIndex].myDoorLocations[doorIndex];
			if (myMap.IndexIsWall(doorMapIndex - 1) == true && myMap.IndexIsWall(doorMapIndex + 1) == true &&
				myMap.IndexIsWall(doorMapIndex - myMap.GetMapWidth()) == false && myMap.IndexIsWall(doorMapIndex + myMap.GetMapWidth()) == false ||
				myMap.IndexIsWall(doorMapIndex - 1) == false && myMap.IndexIsWall(doorMapIndex + 1) == false &&
				myMap.IndexIsWall(doorMapIndex - myMap.GetMapWidth()) == true && myMap.IndexIsWall(doorMapIndex + myMap.GetMapWidth()) == true)
			{
				continue;
			}
			myMap.CreateFloor(doorMapIndex, myMapFactory);
			myRooms[roomIndex].myDoorLocations.RemoveCyclicAtIndex(doorIndex);
		}
	}
}

void RoomGenerator::RemoveRoomsMadeOfWalls()
{
	for (int roomIndex = myRooms.Size() - 1; roomIndex >= 0; --roomIndex)
	{
		if (myMap.IndexIsWall(myRooms[roomIndex].myX + (myRooms[roomIndex].myY) * myMap.GetMapWidth()) == true)
		{
			myRooms.RemoveCyclicAtIndex(roomIndex);
		}
	}
}

void RoomGenerator::CreateRooms(const int aRoomCount, const int aMaxRoomWidth,
	const int aMaxRoomHeight, const int aMinRoomWidth, const int aMinRoomHeight)
{
	int tests = 0;

	while (myRooms.Size() < aRoomCount && tests < 10000)
	{
		int x = (rand() % (myMapSetting.GetMapWidth() - 2)) + 1;
		int y = (rand() % (myMapSetting.GetMapHeight() - 2)) + 1;
		int w = aMinRoomWidth + (rand() % MAX((aMaxRoomWidth - aMinRoomWidth), 1));
		int h = aMinRoomHeight + (rand() % MAX((aMaxRoomHeight - aMinRoomHeight), 1));

		if (x + w >= myMapSetting.GetMapWidth() - 1 || y + h >= myMapSetting.GetMapHeight() - 1)
		{
			continue;
		}

		if (TilesAreWalls(x - 2, y - 2, w + 3, h + 3) == true)
		{
			myMap.CreateRoom(myMapFactory, x, y, w, h);
			Room newRoom(x, y, w, h);

			myRooms.Add(newRoom);
		}

		++tests;
	}
}

void RoomGenerator::InitMap(const int aWidth, const int aHeight)
{
	myRooms.Clear();
	MapGenerationAlgorithm::InitMap(aWidth, aHeight);
}


void RoomGenerator::FurnishRooms()
{
	const auto& roomTypes = myMapSetting.GetRoomTypes();

	for (int i = 0; i < myRooms.Size(); ++i)
	{
		const std::string& roomTypeName = roomTypes[rand() % roomTypes.Size()];
		int nrOfRandomBackdrops = myMapSetting.GetBackdropMinCount() + (rand() % myMapSetting.GetBackdropMaxCount() - myMapSetting.GetBackdropMinCount());

		for (int backDropCount = 0; backDropCount < nrOfRandomBackdrops; ++backDropCount)
		{
			const std::string& randomBackdropName = myRoomTypeManager.GetRoomType(roomTypeName).GetRandomBackdrop();

			Backdrop *backDrop = myMapFactory.CreateBackdrop(randomBackdropName);

			int backdropsOfSameType = backDrop->GetBackdropType().GetMinCount() + rand() % backDrop->GetBackdropType().GetMaxCount();
			for (int j = 0; j < backdropsOfSameType; ++j)
			{
				backDrop = myMapFactory.CreateBackdrop(backDrop->GetBackdropType().GetName());

				int tileIndex = -1;
				switch (backDrop->GetBackdropType().GetBackdropLocation())
				{
				case eBackdropLocation::eRandom:
					tileIndex = myMap.FindRandomFloorTile(myRooms[i]);
					break;
				case eBackdropLocation::eOnWall:
					tileIndex = myMap.FindWall(myRooms[i]);
					break;
				case eBackdropLocation::eAgainstWall:
					tileIndex = myMap.FindTileByWall(myRooms[i]);
					if (tileIndex == NO_TILE_FOUND)
					{
						continue;
					}
					break;
				case eBackdropLocation::eAbsolutCenter:
				{
					tileIndex = myMap.CalculateTileIndexByIndex(myRooms[i].myX + myRooms[i].myWidth / 2,
						myRooms[i].myY + myRooms[i].myHeight / 2);
					if (myMap.CanWalkOnIndex(tileIndex) == true)
					{
						break;
					}
					// if no empty center found in any room, just skip
					if (myMap.CanWalkOnIndex(tileIndex) == false)
					{
						continue;
					}

					break;
				}
				case eBackdropLocation::eCenterSpace:
				{
					tileIndex = myMap.CalculateTileIndexByIndex((myRooms[i].myX + myRooms[i].myWidth / 2) + (rand() % myRooms[i].myWidth / 3) - (rand() % myRooms[i].myWidth / 3),
						(myRooms[i].myY + myRooms[i].myHeight / 2) + (rand() % myRooms[i].myHeight / 3) - (rand() % myRooms[i].myHeight / 3));
					if (myMap.CanWalkOnIndex(tileIndex) == true)
					{
						break;
					}
					// if no empty center found in any room, just skip
					if (myMap.CanWalkOnIndex(tileIndex) == false)
					{
						continue;
					}

					break;
				}
				case eBackdropLocation::eDoorSide:
				{
					if (myRooms[i].myDoorSideLocations.Size() == 0)
					{
						continue;
					}

					int sideLocation = rand() % myRooms[i].myDoorSideLocations.Size();
					int doorSide1 = myRooms[i].myDoorSideLocations[sideLocation].first;
					int doorSide2 = myRooms[i].myDoorSideLocations[sideLocation].second;

					if (myMap.CanWalkOnIndex(doorSide1) == false || myMap.CanWalkOnIndex(doorSide2) == false ||
						myMap.IsBlockingPath(doorSide1) == true || myMap.IsBlockingPath(doorSide2) == true)
					{
						continue;
					}

					myMap.AddBackdrop(backDrop, doorSide1);
					backDrop = myMapFactory.CreateBackdrop(backDrop->GetBackdropType().GetName());
					myMap.AddBackdrop(backDrop, doorSide2);

					continue;
				}
				}

				if (backDrop->GetBackdropType().IsObstacle() == true && myMap.IsBlockingPath(tileIndex) == true)
				{
					continue;
				}

				myMap.AddBackdrop(backDrop, tileIndex);
			}
		}
		myRooms[i].myIsFurnished = true;
	}
}

int	RoomGenerator::GetRoomIDFromTilePosition(const Vector2f& aTilePosition) const
{
	for (int i = 0; i < myRooms.Size(); ++i)
	{
		if (myRooms[i].IsInside(static_cast<int>(aTilePosition.myX), static_cast<int>(aTilePosition.myY)) == true)
		{
			return i;
		}
	}

	return -1;
}

bool RoomGenerator::HasGeneratedEnoughRooms() const
{
	std::set<int> roomsVisited;
	for (int i = 0; i < myMap.GetMapWidth() * myMap.GetMapHeight(); ++i)
	{
		if (myMap.IndexIsWall(i) == false)
		{
			Vector2f tilePos = myMap.CalculatePositionByIndex(i);
			tilePos.myX /= myMap.GetMapWidth();
			tilePos.myY /= myMap.GetMapHeight();
			roomsVisited.emplace(GetRoomIDFromTilePosition(tilePos));
		}
	}

	if (roomsVisited.size() < static_cast<unsigned int>(myMapSetting.GetRoomCount() - 2))
	{
		return false;
	}

	return true;
}

bool RoomGenerator::TilesAreWalls(const int aX, const int aY, const int aWidth, const int aHeight) const
{
	for (int xPos = aX; xPos < aX + aWidth; ++xPos)
	{
		for (int yPos = aY; yPos < aY + aHeight; ++yPos)
		{
			if (myMap.GetTileStatusByIndex(xPos, yPos) != eTileStatus::eWall)
			{
				return false;
			}
		}
	}

	return true;
}

void RoomGenerator::CreateSpatialAreas() 
{
	do
	{
		InitMap(myMapSetting.GetMapWidth(), myMapSetting.GetMapHeight());
		CreateRooms(myMapSetting.GetRoomCount(), myMapSetting.GetRoomMaxWidth(), myMapSetting.GetRoomMaxHeight(),
			myMapSetting.GetRoomMinWidth(), myMapSetting.GetRoomMinHeight());
		CreateCorridors(myMapSetting.GetCorridorRandomFactor());
		CreateEntrance();
		RemoveTilesNotConnectedToEntrance();
	} while (HasGeneratedEnoughRooms() == false);

	RemoveRoomsMadeOfWalls();
	RemoveLonelyDoors();
}

void RoomGenerator::CreateExit()
{
	// empty
}


