#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "TI_TimeManager.h"
#include "StaticArray.h"
#include "CU_Vector.h"

#include "Game.h"


class App
{
public:
	App();
	~App();

	bool Init();
	bool Update();


private:
	Game myGame;

};

#endif