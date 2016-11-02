#pragma once

#include "GrowingArray.h"
#include "Dot.h"

class Player;
class ScoreCounter;


class DotContainer
{
public:
	DotContainer();
	~DotContainer();
	void Init();
	void Update(Player& aPlayer, ScoreCounter& aScoreCounter);
	void Render();
	int GetDotsLeft();

private:
	void LoadDotGrid();
	CU::GrowingArray<Dot*> myDotGrid;
	int myDotsLeft;
};
