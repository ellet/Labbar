#pragma once

#include "GrowingArray.h"

class Enemy;
class Player;
class ScoreCounter;

class EnemyContainer
{
public:
	EnemyContainer();
	~EnemyContainer();
	void Init();
	void Update(Player& aPlayer, ScoreCounter& aScoreCounter);
	void Render();

private:

	CU::GrowingArray<Enemy*> myEnemys;
	int myScore;
};
