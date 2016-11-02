#pragma once

#include "VisualRep.h"
#include "MovementBehaviors.h"

enum LifeStates
{
	ALIVE,
	KILLABLE,
	DEAD,
};

enum EnemyType
{
	RANDOM,
	CHASER,
	AMBUSHER,
};

class Player;


class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init(char* aTexturePath, CU::Vector2f aPosition, EnemyType aEnemyType);
	void Update(Player& aPlayer);
	void Render();
	const CU::Vector2f& GetPosition();
	void SetLifeState(LifeStates aState);
	const LifeStates& GetLifeState();
	void ResetPosition();
	bool IsNotKillable();
	void ResetKillableTimer();
	

private:
	void TimeKillable();
	void Blink();
	void Random();
	void Chaser();
	void Ambusher(Player& aPlayer);

	MovementBehaviors myMovementBehaviors;
	CU::StaticArray<VisualRep,3> myVisualReps;
	CU::Vector2f myPosition;
	CU::Vector2f myStartPosition;
	LifeStates myLifeState;
	float myBlinkTimer;
	float myKillableTimer;
	float myFollowPlayerTimer;
	bool myIsVisible;
	bool myIsFollowingPlayer;
	EnemyType myEnemyType;
};
