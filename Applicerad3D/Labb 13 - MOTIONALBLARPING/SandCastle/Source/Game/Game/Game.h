#pragma once
#include <Engine\PostMaster.h>

namespace SB
{
	class SceneManager;
	class Window;
	struct CloseGameMessage;
}

class Game : public SB::Subscriber<SB::CloseGameMessage>
{
public:
	Game();
	~Game();

	void Start();

	SB::ReceiveResult Receive(const SB::CloseGameMessage & aMessage) override;

private:
	std::unique_ptr<SB::Window> myWindow;
	std::unique_ptr<SB::SceneManager> mySceneManager;

	void Initialize();
	void ProcessMessages();
	void Update(const SB::Time &aDeltaTime);
	void Render();
	void CreatePerspective();

	bool myShouldBeRunning;
};
