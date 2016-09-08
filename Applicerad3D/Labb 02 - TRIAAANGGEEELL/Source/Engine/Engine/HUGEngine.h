#pragma once
#include <functional>

class CHUGWindowsWindow;
class CHUGDXFramework;

class CHUGEngineSingleton
{
public:

	struct EngineParameters
	{
		std::function<void()> myGameUpdateFunction;
		CU::Vector2ui myWindowSize;
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

	CHUGDXFramework * myFramework;

	static CHUGEngineSingleton * ourInstance;

	CHUGWindowsWindow * myWindowsWindow;
	std::function<void()> myGameUpdateFunction;
	bool myShouldRun;
};


