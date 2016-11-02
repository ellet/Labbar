#ifndef MAIN_SINGLETON_HEADER
#define MAIN_SINGLETON_HEADER

#include "TimeManager.h"

namespace FroggerGame
{
    class TileGrid;
    class SpriteContainer;
	class WaterEntityHandler;
	class VehicleHandler;
};

class HGE;

class MainSingleton
{

public:
   
    static void Create(HGE* aHGE);
    void Destroy();
    ~MainSingleton();
    _inline static MainSingleton* GetInstance() {return ourInstance;}
    _inline FroggerGame::TileGrid* GetTileGrid() {return myTileGrid;}
	_inline CommonUtilities::TimeManager* GetTimeManager() {return myTimeManager;}
    _inline FroggerGame::SpriteContainer* GetSpriteContainer() {return mySpriteContainer;}
	_inline FroggerGame::WaterEntityHandler* GetWaterEntityHandler() {return myWaterEntityHandler;}
	_inline FroggerGame::VehicleHandler* GetVehicleHandler() {return myVehicleHandler;}

private:

     MainSingleton();
     void Init(HGE* aHGE);
     static MainSingleton* ourInstance;

     FroggerGame::TileGrid* myTileGrid;
     FroggerGame::SpriteContainer* mySpriteContainer;
	 FroggerGame::VehicleHandler* myVehicleHandler;
	 FroggerGame::WaterEntityHandler* myWaterEntityHandler;
	 CommonUtilities::TimeManager* myTimeManager;
};

#endif