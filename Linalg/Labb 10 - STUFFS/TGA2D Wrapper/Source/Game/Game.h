#pragma once
#include <tga2d/Engine.h>

#include <Syncronizer\Syncronizer.h>
#include "States/LocalTestStates/TestState.h"

class Player;
class Inventory;
class DialogManager;

class CGame
{
public:

	CGame();
	~CGame();
	void Init();
	

private:

	CommonUtilities::Thread::Syncronizer<CGame> mySyncronizer;

	TestState * myTestState;

	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	void ThreadFunctionUpdate();
	void ThreadFunctionRender();
};
