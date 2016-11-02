#include "StdAfx.h"
#include "SpriteContainer.h"

FG::SpriteContainer::SpriteContainer()
{
}

FG::SpriteContainer::~SpriteContainer()
{
}
    
hgeSprite* FG::SpriteContainer::GetSprite(SpriteType aType)
{
    return mySprites[aType];
}

void FG::SpriteContainer::LoadSprites(HGE* aHGE)
{
	myHGE = aHGE;

    mySprites[IDLE_UP_SPRITE]       = LoadSprite("AwesomeArt/Frog/frog_up.dds");
    mySprites[JUMP_UP_SPRITE]       = LoadSprite("AwesomeArt/Frog/frog_jump_up.dds");
    mySprites[IDLE_RIGHT_SPRITE]    = LoadSprite("AwesomeArt/Frog/frog_right.dds");
    mySprites[JUMP_RIGHT_SPRITE]    = LoadSprite("AwesomeArt/Frog/frog_jump_right.dds");

    mySprites[IDLE_DOWN_SPRITE] = LoadSprite("AwesomeArt/Frog/frog_down.dds");
    mySprites[JUMP_DOWN_SPRITE] = LoadSprite("AwesomeArt/Frog/frog_jump_down.dds");
    mySprites[IDLE_LEFT_SPRITE] = LoadSprite("AwesomeArt/Frog/frog_left.dds");
    mySprites[JUMP_LEFT_SPRITE] = LoadSprite("AwesomeArt/Frog/frog_jump_left.dds");

    mySprites[FROG_DEATH_1_SPRITE] = LoadSprite("AwesomeArt/Frog/Frog_death1.dds");
    mySprites[FROG_DEATH_2_SPRITE] = LoadSprite("AwesomeArt/Frog/Frog_death2.dds");

    mySprites[CAR_SPRITE]        = LoadSprite("AwesomeArt/Vehicles/car.dds");
    mySprites[BULLDOZER1_SPRITE] = LoadSprite("AwesomeArt/Vehicles/bulldozer1.dds");
    mySprites[BULLDOZER2_SPRITE] = LoadSprite("AwesomeArt/Vehicles/bulldozer2.dds");
    mySprites[FERARRI_SPRITE]    = LoadSprite("AwesomeArt/Vehicles/ferarri.dds");
    mySprites[TRUCK_SPRITE]      = LoadSprite("AwesomeArt/Vehicles/truck.dds");
    mySprites[BUS_SPRITE]        = LoadSprite("AwesomeArt/Vehicles/bus.dds");

    mySprites[TURTLE_SPRITE]         = LoadSprite("AwesomeArt/WaterEntitys/turtle.dds");
    mySprites[TURTLE_SUB1_SPRITE]    = LoadSprite("AwesomeArt/WaterEntitys/turtle_sub1.dds");
    mySprites[TURTLE_SUB2_SPRITE]    = LoadSprite("AwesomeArt/WaterEntitys/turtle_sub2.dds");
    mySprites[LOG_SMALL_SPRITE]      = LoadSprite("AwesomeArt/WaterEntitys/log3.dds");
    mySprites[LOG_MEDIUM_SPRITE]     = LoadSprite("AwesomeArt/WaterEntitys/log4.dds");
    mySprites[LOG_LARGE_SPRITE]      = LoadSprite("AwesomeArt/WaterEntitys/log5.dds");
	
	//FIX
	mySprites[LOG_SMALL_SPRITE]->SetHotSpot(48, 16);
	mySprites[LOG_MEDIUM_SPRITE]->SetHotSpot(64, 16);
	mySprites[LOG_LARGE_SPRITE]->SetHotSpot(80, 16);
	//--

    mySprites[WORLD_SPRITE]  = LoadSprite("AwesomeArt/Other/World.png");     

    //mySprites[CROCODILE_SPRITE]  = LoadSprite("temp.PNG", aHGE);   

    mySprites[BUG_SPRITE]  = LoadSprite("AwesomeArt/Other/bug.dds");   
    mySprites[TIME_BAR]  = LoadSprite("AwesomeArt/Other/timeBar.png");  
	mySprites[MAIN_MENU_SPRITE] = LoadSprite("AwesomeArt/Other/Menu.png");  
	mySprites[MAIN_MENU_SPRITE]->SetHotSpot(0,0);
	mySprites[GAME_OVER_SPRITE] = LoadSprite("AwesomeArt/Other/GameOver.png");  
	mySprites[GAME_OVER_SPRITE]->SetHotSpot(0,0);
	mySprites[PLAY_AGAIN_SPRITE] = LoadSprite("AwesomeArt/Other/playAgain.png");  
	mySprites[PLAY_AGAIN_SPRITE]->SetHotSpot(0,0);
}

hgeSprite* FG::SpriteContainer::LoadSprite(const char* aFilePath)
{
    HTEXTURE texture = myHGE->Texture_Load(aFilePath);
    float width = static_cast<float>(myHGE->Texture_GetWidth(texture));
    float height = static_cast<float>(myHGE->Texture_GetHeight(texture));
    hgeSprite* newSprite = new hgeSprite(texture, 0, 0, width, height);
    newSprite->SetHotSpot(width*0.5f, height*0.5f);
    return newSprite;
}