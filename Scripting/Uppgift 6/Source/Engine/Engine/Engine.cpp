#include "stdafx.h"
#include "Engine\Engine.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"
#include "Debugging\Debugger.h"
#include "SoundManager\SoundManager.h"
#include "Scripting\ScriptHost.h"
#include "GUI\GUILoader.h"
#include "DataParser\SaveGame\JsonSerializer.h"
#include "EngineSettings.h"

namespace SB
{
	Engine * Engine::ourInstance = nullptr;

	Engine::Engine()
	{
		myRenderer = std::make_unique<DXRenderer>();
		myFileWatcher = new FileChangeWatcher();
		myResourceManager = std::make_unique<ResourceManager>();
		myDebugLogger = std::make_unique<DebugLogger>();
		mySoundManager = std::make_unique<SoundManager>();
		myScriptHost = std::make_shared<ScriptHost>();
		myGUILoader = std::make_unique<GUILoader>();

		SP::CreationManager::Create();

		//Init AppData folder structure for save & config files
		char* buffer;
		size_t bufferSize;
		int success = _dupenv_s(&buffer, &bufferSize, "APPDATA");
		std::string appDataPath = buffer;
		std::string sandCastleFolderPath = appDataPath + "\\Sandcastle";
		std::string gameFolderPath = sandCastleFolderPath + "\\AI-Project";
		std::string saveFolderPath = gameFolderPath + "\\SaveData";
		std::string configFolderPath = gameFolderPath + "\\Config";

		std::string saveDataPath = saveFolderPath + "\\AutoSave.json";
		std::string configDataPath = configFolderPath + "\\config.json";

		CreateDirectoryA(sandCastleFolderPath.c_str(), NULL);
		CreateDirectoryA(gameFolderPath.c_str(), NULL);
		CreateDirectoryA(saveFolderPath.c_str(), NULL);
		CreateDirectoryA(configFolderPath.c_str(), NULL);

		DataDocument configDoc;

		std::ifstream file(configDataPath);
		if (file.fail() == false) //Ensure file exists in appData, otherwise use defaultSettings.json in Data folder
		{
			Data::Open(configDataPath, configDoc);
		}
		else
		{
			Data::Open("Assets/Data/defaultConfig.json", configDoc);
		}

		myEngineSettings = std::make_unique<EngineSettings>(configDoc);
		mySavePath = saveDataPath;
	}

	Engine::~Engine()
	{
		SP::CreationManager::Destroy();
		myResourceManager->RemoveAllResources();
		myResourceManager = nullptr;
		mySoundManager = nullptr;
		myScriptHost = nullptr;
		myRenderer = nullptr;
		myGUILoader = nullptr;
		myDebugger = nullptr;
		myDebugLogger = nullptr;
	}


	DebugDrawer & Engine::GetDebugDrawer()
	{
		return GetInstance().myDebugger->GetDebugDrawer();
	}

	void Engine::CreateInstance()
	{
		assert("Instance already created" && ourInstance == nullptr);

		ourInstance = new Engine();
	}

	void Engine::DestroyInstance()
	{
		assert("Instance not created" && ourInstance != nullptr);

		delete ourInstance;
		ourInstance = nullptr;
	}

	void Engine::AttachDebugger(const std::shared_ptr<Debugger> & aDebugger)
	{
		myDebugger = aDebugger;
	}

	void Engine::Initialize()
	{
		GetInstance().myDebugger->Initialize();
		GetInstance().myRenderer->SetFullscreen(GetInstance().myEngineSettings->GetStartInFullscreen());
	}

}
