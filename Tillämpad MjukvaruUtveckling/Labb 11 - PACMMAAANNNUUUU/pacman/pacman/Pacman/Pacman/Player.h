#ifndef PLAYER_h_
#define PLAYER_h_

#include "VisualRep.h"
#include "StaticArray.h"

enum MoveStates
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Render();

	const CU::Vector2f& GetPosition();
	const float& GetSize();
	void ResetPosition();
	bool IsInvincible();
	void SetIsInvincible(bool aBool);
	void Dead();
	int GetLife();

private:
	void InputUpdate();
	void PortalThePlayer();
	void OpenMouthTimer();

	CU::StaticArray<VisualRep,4> myOpenMouthRep; 
	VisualRep myVisualRep;
	CU::Vector2f myCurrentVelocity;
	CU::Vector2f myVelocity;
	CU::Vector2f myPosition;
	CU::Vector2f myDestination;
	int myLife;
	float mySize;
	float myCheckSize;
	float mySpeed;
	float myMouthTimer;
	bool myIsInvincible;
	bool myMouthIsOpen;

	MoveStates myMoveState;
	MoveStates myCurrentMoveState;
};

#endif
