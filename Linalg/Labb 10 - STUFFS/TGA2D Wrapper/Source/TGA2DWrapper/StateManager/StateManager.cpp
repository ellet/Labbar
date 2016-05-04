#include "StateManager.h"
//#include "CollisionManager.h"

StateManager *StateManager::ourInstance;

bool StateManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new StateManager();
		return true;
	}
	return false;
}
bool StateManager::Destroy()
{
	
	delete ourInstance;
	ourInstance = nullptr;

	return true;

}

void StateManager::AddStates(CU::GrowingArray<BaseState*> & aArrayOfStates)
{
	//TODO::FIX UGLY SOLUTION
	GetInstance()->myStates = aArrayOfStates;
}

void StateManager::InitAllState()
{
	GetInstance()->InternalInitAllStates();
}

void StateManager::InternalInitAllStates()
{
	for (unsigned short iState = 0; iState < myStates.Size(); ++iState)
	{
		myStates[iState]->Init();
	}
}

void StateManager::ChangeState()
{
	DL_ASSERT(myChangeToState != enumGameStates::enumLength, "Invalid change to state!");
	if (myActiveState != enumGameStates::enumLength)
	{
		myStates[static_cast<unsigned short>(myActiveState)]->DoOnChangeFrom();
	}
	myActiveState = myChangeToState;
	myStates[static_cast<unsigned short>(myActiveState)]->DoOnChangeTo();
}

void StateManager::Update(const float aDeltaTime)
{
	if (GetInstance()->myChangeToState != GetInstance()->myActiveState)
	{
		GetInstance()->ChangeState();
	}

	GetInstance()->myStates[static_cast<unsigned short>(GetInstance()->myActiveState)]->Update(aDeltaTime);
}

void StateManager::Draw()
{
	GetInstance()->myStates[static_cast<unsigned short>(GetInstance()->myActiveState)]->Draw();
}

StateManager::StateManager()
{
	myActiveState = enumGameStates::enumLength;
	myStates.Init(4);

}
StateManager::~StateManager()
{
	myStates.DeleteAll();
}


