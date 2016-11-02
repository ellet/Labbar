#pragma once

#include "Player.h"
#include "DotContainer.h"
#include "ScoreCounter.h"
#include "Cherry.h"

#include "EnemyContainer.h"
#include "Conditions.h"


class Game
{
public:
	Game();
	~Game();
	void Init();
	bool Update();
	void Render();

private:

	Player myPlayer;
	DotContainer myDotContainer;
	ScoreCounter myScoreCounter;
	Cherry myCherry;
	EnemyContainer myEnemyContainer;
	Conditions myConditions;

};
