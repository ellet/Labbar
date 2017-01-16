#pragma once

class ScriptSystem
{
public:
	static void Create();
	static void Destroy();

	// Denna funktion ska skicka med en C++ funktion som ska kallas efter att LUA har startas (createstate osv.)
	void Init(const std::function<void()>& aRegisterFunction, const std::string& aFileName);
	
	// Den funktion som ni skickade i init ska kalla följande funktion X antal gånger (en för varje funktion som ska exponeras)
	void RegisterFunction(const std::string& aNameInLua, lua_CFunction aFunction, const std::string& aHelpText);
	
	// C++ TILL LUA, LuaArgs är en array av argument
	void CallFunction(const std::string& aNameInLua, const LuaArgs& someArgs);

	// Ska kalla de LUA funktioner som kräver en "frame" update
	void Update();


	static ScriptSystem* GetInstance();

private:
	void CheckError(int aError);
	void PrintDocumentation();
	ScriptSystem();
	~ScriptSystem();

	static ScriptSystem* myInstance;
	lua_State* myState; // Ett state. Vi kan lägga på fler sen. Det är OK att göra detta till en array
};

