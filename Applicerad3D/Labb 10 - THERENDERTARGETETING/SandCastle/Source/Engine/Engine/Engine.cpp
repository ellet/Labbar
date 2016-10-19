#include "stdafx.h"
#include "Engine\Engine.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\FileWatcher\FileChangeWatcher.h"
#include "Debugging\Debugger.h"
#include "SoundManager\SoundManger.h"
#include "Scripting\ScriptHost.h"

namespace ENGINE_NAMESPACE
{
	Engine * Engine::ourInstance = nullptr;

	Engine::Engine()
	{
		myRenderer = std::make_unique<DXRenderer>();
		myFileWatcher = new FileChangeWatcher();
		myResourceManager = std::make_unique<ResourceManager>();
		myDebugLogger = std::make_unique<DebugLogger>();
		mySoundManager = std::make_unique<SoundManger>();
		myScriptHost = std::make_shared<ScriptHost>();
	}

	Engine::~Engine()
	{
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
}
