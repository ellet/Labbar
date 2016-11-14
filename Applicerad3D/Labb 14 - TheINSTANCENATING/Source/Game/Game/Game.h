#pragma once
#include <Engine\PostMaster.h>
#include "Player\PlayerDataStruct.h"

namespace SB
{
	class SceneManager;
	class Window;
	class Cursor;
	struct CloseGameMessage;
}

class LevelProgressionManager;

class Game : public SB::Subscriber<SB::CloseGameMessage>
{
public:
	void Start();
	static void CreateInstance();
	static Game & GetInstance();
	static void DestroyInstance();
	SavedPlayerData & GetPlayerSavedData();

	SB::ReceiveResult Receive(const SB::CloseGameMessage & aMessage) override;

private:
	static LevelProgressionManager & GetProgressionManager();


	Game();
	~Game();
	
	std::unique_ptr<SB::Cursor> myCursor;
	std::unique_ptr<SB::Window> myWindow;
	std::unique_ptr<SB::SceneManager> mySceneManager;
	std::unique_ptr<LevelProgressionManager> myLevelProgressionManager;

	SavedPlayerData mySavedData;

	static Game * ourInstance;

	void Initialize();
	void ProcessMessages();
	void Update(const SB::Time &aDeltaTime);
	void Render();
	void CreatePerspective();

	bool myShouldBeRunning;
};

inline Game & Game::GetInstance()
{
	assert(ourInstance != nullptr && "Game not created");
	return *ourInstance;
}

inline LevelProgressionManager & Game::GetProgressionManager()
{
	return *GetInstance().myLevelProgressionManager;
}

inline SavedPlayerData & Game::GetPlayerSavedData()
{
	return GetInstance().mySavedData;
}


