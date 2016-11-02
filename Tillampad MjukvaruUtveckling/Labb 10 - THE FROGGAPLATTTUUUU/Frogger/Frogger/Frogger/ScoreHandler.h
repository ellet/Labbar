#ifndef SCORE_HANDLER_HEADER
#define SCORE_HANDLER_HEADER

#include "..\hgelibs\include\hgefont.h"
#include "..\hgelibs\include\hgesprite.h"
#include "namespaces.h"
#include "Vector2.h"
#include "StaticArray.h"

namespace FroggerGame
{
    class Frog;
    struct Tile;

    struct FrogHome
    {
        Tile* myFirstTile;
        Tile* mySecondTile;
        CU::Vector2f myPosition;
        bool myIsTaken;
		bool myHasBug;
    };    

    class ScoreHandler
    {

    public:

        ScoreHandler();
        ~ScoreHandler();
        void Init(Frog* aFrog);
        void ReInit();
        void Update();
        void Render();

		bool LevelCompleted();

    private:

        void InitFont();
        void InitFrogHomes();

        void HandleMovementScore();
        void HandleFrogHomes();
		void HandleBugSpawn();
		void AddBug();

        CU::StaticArray<FrogHome, 5> myFrogHomes;

		//bugs
		float myBugSpawnTimer;
		float myTimeForBugToStay;
		int myCurrentBugIndex;
		//--

        float myCurrentLevelToGetScore; 
		bool myHasFoundHome;
        
        Frog* myFrog;
        hgeFont* myFont;
        hgeSprite* myFrogSprite;
    };
};

#endif
