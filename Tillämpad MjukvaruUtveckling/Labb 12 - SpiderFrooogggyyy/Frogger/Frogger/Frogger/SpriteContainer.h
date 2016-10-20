#ifndef SPRITE_CONTAINER_HEADER
#define SPRITE_CONTAINER_HEADER

#include "defines.h"
#include "namespaces.h"
#include "StaticArray.h"
#include "..\hgelibs\include\hge.h"
#include "..\hgelibs\include\hgesprite.h"

namespace FroggerGame
{
    enum SpriteType
    {
        //FROG
        IDLE_UP_SPRITE,
        JUMP_UP_SPRITE,
        IDLE_RIGHT_SPRITE,
        JUMP_RIGHT_SPRITE,
        IDLE_DOWN_SPRITE,
        JUMP_DOWN_SPRITE,
        IDLE_LEFT_SPRITE,
        JUMP_LEFT_SPRITE,

		FROG_DEATH_1_SPRITE,
		FROG_DEATH_2_SPRITE,

        //VEHICLES
        CAR_SPRITE,
        BULLDOZER1_SPRITE,
        BULLDOZER2_SPRITE,
        FERARRI_SPRITE,
        TRUCK_SPRITE,
        BUS_SPRITE,

        //WATER ENTITYS
        TURTLE_SPRITE,
        TURTLE_SUB1_SPRITE,
        TURTLE_SUB2_SPRITE,
        LOG_SMALL_SPRITE,
        LOG_MEDIUM_SPRITE,
        LOG_LARGE_SPRITE,

        //OTHER
        WORLD_SPRITE,        
        CROCODILE_SPRITE,
        BUG_SPRITE,
        TIME_BAR,
		MAIN_MENU_SPRITE,
		GAME_OVER_SPRITE,
		PLAY_AGAIN_SPRITE,

        NUM_SPRITE_TYPES,
    };

    class SpriteContainer
    {

    public:

        SpriteContainer();
        ~SpriteContainer();       
        void LoadSprites(HGE* aHGE);
        hgeSprite* GetSprite(SpriteType aType);

    private:        

        hgeSprite* LoadSprite(const char* aFilePath);

        CU::StaticArray<hgeSprite*, NUM_SPRITE_TYPES> mySprites; 

		HGE* myHGE;
    };
};

#endif
