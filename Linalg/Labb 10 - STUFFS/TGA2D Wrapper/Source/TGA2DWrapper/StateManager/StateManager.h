#pragma once

#include <GrowingArray\GrowingArray.h>

#include "StatesEnum.h"

#include "..\BaseClasses\BaseState\BaseState.h"
#include <DLDebug/DL_Debug.h>
#include <NameSpaceAliases.h>

class StateManager
{
public:

	static bool Create();
	static bool Destroy();

	static void inline SetActiveState(const enumGameStates aState);
	static void InitAllState();

	static void Update(const float aDeltaTime);
	static void Draw();

	static void AddStates(CU::GrowingArray<BaseState*> & aArrayOfStates);
private:

	static StateManager *ourInstance;

	void InternalInitAllStates();
	void ChangeState();
	
	CU::GrowingArray<BaseState*> myStates;
	enumGameStates myActiveState;
	enumGameStates myChangeToState;

	StateManager();
	~StateManager();

	static inline StateManager* GetInstance();

};

void StateManager::SetActiveState(const enumGameStates aState)
{
	GetInstance()->myChangeToState = aState;
}

inline StateManager* StateManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "StateManager instance is nullptr");
	return ourInstance;
}
