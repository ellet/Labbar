#pragma once

struct lua_State;

namespace SB
{
	class GameObject;
	class ScriptFile;

	class Script
	{
	public:
		Script(lua_State * aState, ScriptFile & aScriptFile, int aLuaRef);
		~Script();

		void UpdateRef(int aLuaRef);

		

		template <typename ... TArgs>
		void ExecuteFunction(const char * aFunctionName, TArgs && ...aArgs);
		
		void LinkGameObject(GameObject & aObject);
		GameObject & GetLinkedGameObject();
		void MakeOrphan();

	private:

		void Push(const float aValue);
		void Push(const int aValue);
		void Push(const char *aValue);
		void Push(const std::string &aValue);

		template <typename TArg, typename ... TArgs>
		void PushArguments(TArg &&aArg, TArgs &&... aArgs);

		template <typename TArg>
		void PushArguments(TArg &&aArg);

		void PushArguments();
		void CallFunction(const char *aFunctionName);

		ScriptFile * myScriptFile;
		lua_State * L;
		int myLuaRef;
		int myArgumentCount;
		void ** myUserData;
		GameObject *myLinkedGameObject;
		std::string myPath;
	};

	template <typename ... TArgs>
	void Script::ExecuteFunction(const char * aFunctionName, TArgs && ... aArgs)
	{
		PushArguments(aArgs...);
		CallFunction(aFunctionName);
	}

	template <typename TArg, typename ... TArgs>
	void Script::PushArguments(TArg && aArg, TArgs && ... aArgs)
	{
		Push(aArg);
		PushArguments(aArgs...);
	}

	template <typename TArg>
	void Script::PushArguments(TArg &&aArg)
	{
		Push(aArg);
	}

	inline GameObject & Script::GetLinkedGameObject()
	{
		return *myLinkedGameObject;
	}
}
