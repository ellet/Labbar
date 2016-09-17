#pragma once
#include <functional>

class CHUGWindowsWindow;
class CHUGDXFramework;
class CHUGModelManager;
class CHUGCameraManager;
class CDXModel;

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
	static void * GetHWND();

	static void CloseGame();

	static CHUGDXFramework & GetFramework();

	static CDXModel & GetModel(const std::string & aFilePath);
	static CDXModel & GetModel();

private:
	CHUGEngineSingleton();
	~CHUGEngineSingleton();

	void EngineLoop();
	void CreateWindowsWindow();

	static CHUGEngineSingleton & GetInstance();

	//Engine necessary
	CHUGDXFramework * myFramework;
	static CHUGEngineSingleton * ourInstance;
	CHUGWindowsWindow * myWindowsWindow;

	//Extras
	CHUGModelManager * myModelManager;
	CHUGCameraManager * myCameraManager;

	//Function pointers to game for abstraction
	std::function<void()> myGameInitFunction;
	std::function<void()> myGameUpdateFunction;
	std::function<void()> myGameRenderFunction;

	//TODO^^ Set shouldRun with messages
	bool myShouldRun;
};


