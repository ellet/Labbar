#ifndef FROGGER_GAME_HEADER
#define FROGGER_GAME_HEADER

#include "namespaces.h"
#include "..\hgelibs\include\hge.h"
#include "..\hgelibs\include\hgesprite.h"
#include "World.h"
#include "ScoreHandler.h"
#include "TimeHandler.h"
#include "VehicleHandler.h"
#include "WaterEntityHandler.h"
#include "Frog.h"

namespace FroggerGame
{
    class Game
    {

    public:

        Game();
        ~Game();
        void Init(HGE* aHGE);
        bool Update();
        void Render();

    private:

		void CheckForWinLooseConditions();
		void CompleteLevel();
		bool HandlePlayAgain();

        ScoreHandler myScoreHandler;
        TimeHandler myTimeHandler;
        World myWorld;
        Frog myFrog;

        HGE* myHGE;

		float myGameOverScreenTimer;

		bool myGameHasStarted;
		bool myGameOverFlag;
		bool myPlayAgainFlag;
    };
};

#endif
