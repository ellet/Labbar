#pragma once
#include <tga2d/Engine.h>

//#include <Syncronizer\Syncronizer.h>
#include <NameSpaceAliases.h>
#include <StateManager/StatesEnum.h>
#include "Settings\Settings.h"
#include <TestSyncronizer\Syncronizer.h>
#include <TestSyncronizer\ThreadData.h>

class Player;
class Inventory;
class DialogManager;

class CGame
{
public:

	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"");
	

private:

	//CommonUtilities::Thread::Syncronizer<CGame> mySyncronizer;

	Syncronizer mySyncronizer;

	void StatesToLoad(CU::GrowingArray<enumGameStates> & aVectorOfStatesToAddToo);
	void AddStates();

	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	void ThreadFunctionUpdate(ThreadData * const myThreadData);
	void ThreadFunctionRender(ThreadData * const myThreadData);
	Settings mySettings;

	Player *myPlayer;
	Inventory *myInventory;

	bool myIsFullscreen;

};
