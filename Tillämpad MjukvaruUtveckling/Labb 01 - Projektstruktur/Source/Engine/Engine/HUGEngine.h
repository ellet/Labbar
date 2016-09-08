#pragma once
#include <functional>

class CHUGWindowsWindow;

class CHUGEngineSingleton
{
public:

	struct EngineParameters
	{
		std::function<void()> myGameUpdateFunction;
		CU::Vector2i myWindowSize;
		std::string myApplicationName;
	};

	static void Create();
	static void Destroy();

	static void Init(EngineParameters & someParameters);

	static void CloseGame();

private:
	CHUGEngineSingleton();
	~CHUGEngineSingleton();

	static CHUGEngineSingleton & GetInstance();

	void EngineLoop();
	void CreateWindowsWindow();

	static CHUGEngineSingleton * ourInstance;

	CHUGWindowsWindow * myWindowsWindow;
	std::function<void()> myGameUpdateFunction;
	bool myShouldRun;
};


