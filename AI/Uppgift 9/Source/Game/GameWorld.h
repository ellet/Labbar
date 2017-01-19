#pragma once
#include "Input\InputListener.h"
#include "Actors\Actor.h"

class BDSprite;
class TeamBasedGameController;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render() const;

private:
	InputListener myInput;
	
	SB::GrowingArray<BDSprite> mySprites;
};