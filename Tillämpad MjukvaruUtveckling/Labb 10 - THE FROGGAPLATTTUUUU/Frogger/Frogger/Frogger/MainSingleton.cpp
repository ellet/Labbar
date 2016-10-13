#include "StdAfx.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"
#include "TimeManager.h"
#include "WaterEntityHandler.h"
#include "VehicleHandler.h"

MainSingleton* MainSingleton::ourInstance = NULL;

MainSingleton::MainSingleton()
{
    myTileGrid = NULL;
	myTimeManager = NULL;
    mySpriteContainer = NULL;
	myVehicleHandler = NULL;
	myWaterEntityHandler = NULL;
}

MainSingleton::~MainSingleton()
{
}

void MainSingleton::Create(HGE* aHGE)
{
    if(ourInstance == NULL)
    {
        ourInstance = new MainSingleton();
        ourInstance->Init(aHGE);
    }
    else
    {
        assert(false && "Error: MainSingleton already created!");
    }    
}

void MainSingleton::Destroy()
{
    delete(myTileGrid);
	delete(myTimeManager);
    delete(mySpriteContainer);
	delete(myVehicleHandler);
	delete(myWaterEntityHandler);
}

void MainSingleton::Init(HGE* aHGE)
{
    myTileGrid = new FroggerGame::TileGrid();
    myTileGrid->Init();

	myTimeManager = new CU::TimeManager();

    mySpriteContainer = new FroggerGame::SpriteContainer();
    mySpriteContainer->LoadSprites(aHGE);

	myVehicleHandler = new FroggerGame::VehicleHandler();

	myWaterEntityHandler = new FroggerGame::WaterEntityHandler();
	
}
