#ifndef FROGGER_WORLD_HEADER
#define FROGGER_WORLD_HEADER

#include "namespaces.h"
#include "..\hgelibs\include\hgesprite.h"
#include "LevelDataHandler.h"

namespace FroggerGame
{
	class Vehicle;
	class Car;
    class Frog;

    class World
    {

    public:

        World();
        ~World();
        void Init(Frog* aFrog);
		void LoadLevel(Level aLevel);
        void Update();
        void Render();
        int GetCurrentLevel();

    private:           

		void InitWorld();

		LevelDataHandler myLevelDataHandler;
		int myCurrentLevel;

		Frog* myFrog;
		hgeSprite* myWorldSprite;
    };
};

#endif
