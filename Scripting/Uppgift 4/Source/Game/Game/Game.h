#pragma once
#include <Engine\PostMaster.h>

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

	SB::ReceiveResult Receive(const SB::CloseGameMessage & aMessage) override;

private:
	Game();
	~Game();
	
	std::unique_ptr<SB::Cursor> myCursor;
	std::unique_ptr<SB::Window> myWindow;
	std::unique_ptr<SB::SceneManager> mySceneManager;

	static Game * ourInstance;

	void Initialize();
	void ProcessMessages();
	void Update(const SB::Time &aDeltaTime);
	void Render();

	bool myShouldBeRunning;
};

inline Game & Game::GetInstance()
{
	assert(ourInstance != nullptr && "Game not created");
	return *ourInstance;
}
