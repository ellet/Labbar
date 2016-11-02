#pragma once

#include "VisualRep.h"
#include "CU_Vector.h"

class Player;
class ScoreCounter;

class Cherry
{
public:
	Cherry();
	~Cherry();
	void Init();
	void Update(Player& aPlayer, ScoreCounter& aScoreCounter);
	void Render();

private:
	VisualRep myVisualRep;
	float myTimer;
	bool myIsVisible;
	CU::Vector2f myPosition;
};
