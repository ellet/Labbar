#include "stdafx.h"
#include "Engine\Engine.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"
#include "Debugging\Debugger.h"
#include "SoundManager\SoundManager.h"
#include "Scripting\ScriptHost.h"
#include "GUI\GUILoader.h"
#include "DataParser\SaveGame\JsonSerializer.h"

namespace ENGINE_NAMESPACE
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

		char* buffer;
		size_t bufferSize;
		int success = _dupenv_s(&buffer, &bufferSize, "APPDATA");
		std::string path = buffer;
		std::string folderPath = buffer;
		folderPath += "\\SandCastle";
		path = folderPath + "\\PSVSave.json";

		CreateDirectoryA(folderPath.c_str(), NULL);

		myJsonSerializer = std::make_unique<JsonSerializer>(path.c_str());
	}

	Engine::~Engine()
	{
		myResourceManager->RemoveAllResources();
		myResourceManager = nullptr;
		mySoundManager = nullptr;
		myScriptHost = nullptr;
		myRenderer = nullptr;
		myGUILoader = nullptr;
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
	}

}
