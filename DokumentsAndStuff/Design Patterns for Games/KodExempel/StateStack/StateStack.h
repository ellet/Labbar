#pragma once
#include "../CommonUtilities/GrowingArray.h"

class GameState;

class StateStack
{
public:
							StateStack();
							~StateStack();
	void					PushGameState(GameState* aGameState);
	void					PushMainGameState(GameState* aGameState);
	bool					UpdateCurrentState();
	void					RenderCurrentState();
	void					Clear();

private:
	CU::GrowingArray<CU::GrowingArray<GameState*>>
							myGameStates;
	void					PopGameState();
	void					PopMainGameState();
	void					RenderStateAtIndex(int aStateIndex);
	int						myMainGameStateIndex;
	int						myGameStateIndex;

};

