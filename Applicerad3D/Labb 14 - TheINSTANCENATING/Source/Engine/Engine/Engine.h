#pragma once

namespace ENGINE_NAMESPACE
{
	class DXRenderer;
	class FileChangeWatcher;
	class ResourceManager;
	class DebugLogger;
	class Debugger;
	class SoundManager;
	class ScriptHost;
	class GUILoader;
	class JsonSerializer;
	class DebugDrawer;

	class Engine
	{
	public:
		static DXRenderer & GetRenderer();
		static FileChangeWatcher & GetFileWatcher();
		static ResourceManager & GetResourceManager();
		static DebugLogger & GetLogger();
		static Debugger & GetDebugger();
		static DebugDrawer & GetDebugDrawer();
		static SoundManager & GetSoundManager();
		static ScriptHost & GetScriptHost();
		static GUILoader & GetGUILoader();
		static JsonSerializer & GetJsonSerializer();

		static void CreateInstance();
		static Engine & GetInstance();
		static void DestroyInstance();

		void AttachDebugger(const std::shared_ptr<Debugger> & aDebugger);

		static void Initialize();

	private:
		Engine();
		~Engine();

		std::unique_ptr<DXRenderer> myRenderer;
		FileChangeWatcher * myFileWatcher;
		std::unique_ptr<ResourceManager> myResourceManager;
		std::unique_ptr<DebugLogger> myDebugLogger;
		std::unique_ptr<GUILoader> myGUILoader;
		std::shared_ptr<Debugger> myDebugger;
		std::shared_ptr<SoundManager> mySoundManager;
		std::shared_ptr<ScriptHost> myScriptHost;
		std::shared_ptr<JsonSerializer> myJsonSerializer;

		static Engine * ourInstance;
	};

	inline Engine & Engine::GetInstance()
	{
		assert("Engine not created" && ourInstance != nullptr);
		return *ourInstance;
	}

	inline DXRenderer & Engine::GetRenderer() {
		return *GetInstance().myRenderer;
	}

	inline FileChangeWatcher & Engine::GetFileWatcher()
	{
		return *GetInstance().myFileWatcher;
	}

	inline ResourceManager& Engine::GetResourceManager()
	{
		return *GetInstance().myResourceManager;
	}

	inline DebugLogger& Engine::GetLogger()
	{
		return *GetInstance().myDebugLogger;
	}

	inline Debugger & Engine::GetDebugger()
	{
		if (GetInstance().myDebugger == nullptr)
		{
			Error("No debugger is attached!");
		}
		return *GetInstance().myDebugger;
	}

	inline SoundManager & Engine::GetSoundManager()
	{
		return *GetInstance().mySoundManager;
	}

	inline ScriptHost & Engine::GetScriptHost()
	{
		return *GetInstance().myScriptHost;
	}

	inline GUILoader & Engine::GetGUILoader()
	{
		return *GetInstance().myGUILoader;
	}

	inline JsonSerializer & Engine::GetJsonSerializer()
	{
		return *GetInstance().myJsonSerializer;
	}
}
