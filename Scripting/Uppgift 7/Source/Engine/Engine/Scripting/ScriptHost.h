#pragma once

struct lua_State;

namespace SB
{
	class Script;
	class ScriptFile;

	class ScriptHost
	{
	public:
		ScriptHost();

		void RegisterFunctions();

		~ScriptHost();

		ScriptFile * LoadScriptFile(const std::string & aPath);
		void RegisterFunction(const char * aFunctionName, const std::function<int(GameObject&, lua_State*)> & aFunction);

	private:
		lua_State * L;
		static int LuaGetFunction(lua_State * L);
		static int LuaExecuteFunction(lua_State * L);
		std::function<int(GameObject&, lua_State*)> * myLuaFunctionToExecute;
		std::unordered_map<std::string, std::function<int(GameObject&, lua_State*)>*> myLuaFunctions;
	};
}
