#pragma once
#include <functional>

class CHUGWindowsWindow;
class CHUGDXFramework;

class CHUGEngineSingleton
{
public:

	struct EngineParameters
	{
		std::function<void()> myGameInitFunction;
		std::function<void()> myGameUpdateFunction;
		std::function<void()> myGameRenderFunction;
		CU::Vector2ui myWindowSize;
		std::string myApplicationName;
	};

	static void Create();
	static void Destroy();

	static void Init(EngineParameters & someParameters);

	static void ResizeWindow(const CU::Vector2ui aNewWindowSize);

	static void CloseGame();

	static CHUGDXFramework & GetFramework();

private:
	CHUGEngineSingleton();
	~CHUGEngineSingleton();

	static CHUGEngineSingleton & GetInstance();

	void EngineLoop();
	void CreateWindowsWindow();

	CHUGDXFramework * myFramework;

	static CHUGEngineSingleton * ourInstance;

	CHUGWindowsWindow * myWindowsWindow;
	std::function<void()> myGameInitFunction;
	std::function<void()> myGameUpdateFunction;
	std::function<void()> myGameRenderFunction;
	bool myShouldRun;
};


