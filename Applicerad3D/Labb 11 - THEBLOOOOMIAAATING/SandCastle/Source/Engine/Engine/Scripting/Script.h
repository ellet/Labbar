#pragma once

struct lua_State;

namespace ENGINE_NAMESPACE
{
	class GameObject;
	class ScriptFile;

	class Script
	{
	public:
		Script(lua_State * aState, ScriptFile & aScriptFile, int aLuaRef);
		~Script();

		void UpdateRef(int aLuaRef);

		void PushFloat(const float aValue);
		void PushInt(const int aValue);
		void PushString(const char *aValue);

		void ExecuteFunction(const char * aFunctionName);

		void LinkGameObject(GameObject & aObject);
		GameObject & GetLinkedGameObject();

	private:
		ScriptFile * myScriptFile;
		lua_State * L;
		int myLuaRef;
		int myArgumentCount;
		void ** myUserData;
		GameObject *myLinkedGameObject;
	};

	inline GameObject & Script::GetLinkedGameObject()
	{
		return *myLinkedGameObject;
	}
}
