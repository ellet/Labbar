#include "StdAfx.h"
#include "World.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"
#include "TileGrid.h"
#include "Vehicle.h"
#include "Car.h"
#include "Frog.h"
#include "VehicleHandler.h"
#include "WaterEntityHandler.h"
#include "Renderer.h"

FG::World::World()
{
}

FG::World::~World()
{
}

void FG::World::Init(Frog* aFrog)
{
	InitWorld();

	myFrog = aFrog;

    myWorldSprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(WORLD_SPRITE);
    myWorldSprite->SetHotSpot(0,0);  

	myLevelDataHandler.Init();

	myCurrentLevel = -1;
}

void FG::World::LoadLevel(Level aLevel)
{
	if(myCurrentLevel == -1)
	{
		MainSingleton::GetInstance()->GetVehicleHandler()->Init(myLevelDataHandler.GetLevelData(aLevel));
		MainSingleton::GetInstance()->GetWaterEntityHandler()->Init(myLevelDataHandler.GetLevelData(aLevel));
	}
	else
	{
		MainSingleton::GetInstance()->GetVehicleHandler()->ReInit(myLevelDataHandler.GetLevelData(aLevel));
		MainSingleton::GetInstance()->GetWaterEntityHandler()->ReInit(myLevelDataHandler.GetLevelData(aLevel));
	}

	myCurrentLevel = aLevel;
}

void FG::World::InitWorld()
{
	for(int x = 0; x < GRIDSIZE_X; x++)
	{
		for(int y = 0; y < GRIDSIZE_Y; y++)
		{
			FroggerGame::Tile* tile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[x][y];

			if(y < 6)
			{
				tile->myIsWater = true;
			}
			else
			{
				tile->myIsWater = false;
			}
		}
	}
}

int FG::World::GetCurrentLevel()
{
    return myCurrentLevel;
}

void FG::World::Update()
{
	MainSingleton::GetInstance()->GetVehicleHandler()->Update(myFrog);
	MainSingleton::GetInstance()->GetWaterEntityHandler()->Update(myFrog);
}

void FG::World::Render()
{
	//myWorldSprite->Render(0, 0);
	MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*myWorldSprite, CommonUtilities::Vector2f(0.f, 0.f));
	MainSingleton::GetInstance()->GetVehicleHandler()->Render();
	MainSingleton::GetInstance()->GetWaterEntityHandler()->Render();
}
