// Diablo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game\Game.h"
#include <time.h>

int main()
{
	std::srand(static_cast<unsigned int>(time(0)));

	Game TheGame;

	TheGame.RunGame();
	return 0;
}

