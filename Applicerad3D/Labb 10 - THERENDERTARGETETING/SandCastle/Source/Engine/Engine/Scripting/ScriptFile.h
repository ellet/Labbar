#pragma once
#include "Engine/Resources/ResourceManager.h"

struct lua_State;

namespace ENGINE_NAMESPACE
{
	class Script;
	class ScriptHost;

	class ScriptFile : public Resource
	{
	public:
		ScriptFile(lua_State * aState, const std::string & aPath);
		~ScriptFile();

		std::shared_ptr<Script> Execute();
		void Reload() override;
		void RemoveScript(Script & aScript);

	private:
		friend class ScriptHost;

		int ExecuteAndGetRef();

		lua_State * L;
		GrowingArray<Script*> myScripts;
		int myFunctionReference;
	};

}