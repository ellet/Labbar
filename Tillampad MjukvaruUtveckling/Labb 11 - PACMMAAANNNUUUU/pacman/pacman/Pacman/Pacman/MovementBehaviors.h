#pragma once

#include "CU_Vector.h"
#include "StaticArray.h"
#include "GrowingArray.h"

enum Direction
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
};

class Player;

class MovementBehaviors
{
public:
	MovementBehaviors();
	~MovementBehaviors();
	void Init(CU::Vector2f& aPosition);

	void MoveRandom();
	bool MoveHome();
	bool MoveToPlayer(Player& aPlayer);
	void PortalThePlayer();
	void SetSpeed(float aSpeed);
	void ResetSpeed();
	void NewDirection();
	void ResetWaypoints();

	

private:
	void FindNewWaypoints(CU::Vector2f aEndPosition);
	CU::Vector2f* myPosition;
	CU::Vector2f myOriginalPosition;
	CU::Vector2f myDestination;
	CU::StaticArray<CU::Vector2f,4> myDirections;
	CU::GrowingArray<CU::Vector2f> myWalkable;
	CU::Vector2f myVelocity;
	CU::GrowingArray<CU::Vector2f> myWaypoints;

	float mySpeed;
};
