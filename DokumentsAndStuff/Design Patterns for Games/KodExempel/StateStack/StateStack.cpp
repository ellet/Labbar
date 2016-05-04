#include "stdafx.h"
#include "StateStack.h"
#include "GameState.h"
#include <assert.h>

StateStack::StateStack()
{
	myMainGameStateIndex = -1;
	myGameStateIndex = -1;
}


StateStack::~StateStack()
{
	myMainGameStateIndex = -1;
	myGameStateIndex = -1;
}

void StateStack::PopGameState()
{
	assert(myGameStates.Size() != 0 && "Can't pop empty stack!");

	myGameStates[myMainGameStateIndex][myGameStateIndex]->EndState();

	delete myGameStates[myMainGameStateIndex][myGameStateIndex];

	myGameStates[myMainGameStateIndex].RemoveCyclicAtIndex(myGameStateIndex);
	--myGameStateIndex;
}

void StateStack::PopMainGameState()
{
	while (myGameStates[myMainGameStateIndex].Size() > 0)
	{
		PopGameState();
	}

	myGameStates.RemoveCyclicAtIndex(myMainGameStateIndex);

	--myMainGameStateIndex;
	if (myMainGameStateIndex >= 0)
	{
		myGameStateIndex = myGameStates[myMainGameStateIndex].Size() - 1;
	}
	else
	{
		myGameStateIndex = -1;
	}
}

void StateStack::PushGameState(GameState* aGameState)
{
	assert(myGameStates.Size() != 0 && "Can't push game state. No main game state present!");
	myGameStates[myMainGameStateIndex].Add(aGameState);
	aGameState->InitState();
	
	myGameStateIndex = myGameStates[myMainGameStateIndex].Size() - 1;
}

void StateStack::PushMainGameState(GameState* aGameState)
{
	myGameStates.Add(CU::GrowingArray<GameState*>());
	myMainGameStateIndex = myGameStates.Size() - 1;
	PushGameState(aGameState);
}

bool StateStack::UpdateCurrentState()
{
	assert(myGameStates.Size() > 0 && "StateStack has no states!");
	switch (myGameStates[myMainGameStateIndex][myGameStateIndex]->Update())
	{
	case eStateStatus::ePopState:
		PopGameState();
		break;
	case eStateStatus::ePopMainState:
		PopMainGameState();
		break;
	case eStateStatus::eKeepState:
		break;
	}

	return (myGameStates.Size() > 0);
}

void StateStack::RenderCurrentState()
{
	assert(myGameStates.Size() > 0 && "No gamestate is present!");
	RenderStateAtIndex(myGameStateIndex);
}

void StateStack::RenderStateAtIndex(int aStateIndex)
{
	if (aStateIndex < 0)
	{
		return;
	}

	if (myGameStates[myMainGameStateIndex][aStateIndex]->LetThroughRender() == true)
	{
		RenderStateAtIndex(aStateIndex - 1);
	}

	myGameStates[myMainGameStateIndex][aStateIndex]->Render();
}

void StateStack::Clear()
{
	while (myGameStates.Size() > 0)
	{
		PopMainGameState();
	}
}