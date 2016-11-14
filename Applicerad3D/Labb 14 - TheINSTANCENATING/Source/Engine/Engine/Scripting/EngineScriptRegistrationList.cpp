#include "stdafx.h"

#include "Engine/Scripting/ScriptHost.h"
#include "EngineScriptRegistrationList.h"
#include "lua.hpp"


namespace ENGINE_NAMESPACE
{
	namespace SceneReg
	{
		static void RegisterFunctions()
		{
			Engine::GetInstance().GetScriptHost().RegisterFunction("SaveScene", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				SB::PostMaster::Post(SaveLevelMessage());
				return 0;
			}));
		}
	}
	namespace GameObjectReg
	{
		static void RegisterFunctions()
		{
			Engine::GetInstance().GetScriptHost().RegisterFunction("SetPosition", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				aObject.SetPosition(Vector3f(static_cast<float>(lua_tonumber(aLuaStack, 2)),
					static_cast<float>(lua_tonumber(aLuaStack, 3)),
					static_cast<float>(lua_tonumber(aLuaStack, 4))));
				return 0;
			}));
			Engine::GetInstance().GetScriptHost().RegisterFunction("GetPosition", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				lua_pushnumber(aLuaStack, aObject.GetPosition().x);
				lua_pushnumber(aLuaStack, aObject.GetPosition().y);
				lua_pushnumber(aLuaStack, aObject.GetPosition().z);
				return 3;
			}));

			Engine::GetInstance().GetScriptHost().RegisterFunction("RotateAroundLocal", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				aObject.GetRotation().RotateAroundLocalX(DEGREES_TO_RADIANSF(static_cast<float>(lua_tonumber(aLuaStack, 2))));
				aObject.GetRotation().RotateAroundLocalY(DEGREES_TO_RADIANSF(static_cast<float>(lua_tonumber(aLuaStack, 3))));
				aObject.GetRotation().RotateAroundLocalZ(DEGREES_TO_RADIANSF(static_cast<float>(lua_tonumber(aLuaStack, 4))));
				return 0;
			}));
		}
	};
	namespace PrefabReg
	{
		static void RegisterFunctions()
		{
			Engine::GetInstance().GetScriptHost().RegisterFunction("SpawnPrefabAtPosition", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				ObjectPtr newObject = aObject.GetScene().CreateGameObjectFromPrefab(lua_tostring(aLuaStack, 2));
				
				newObject->SetPosition(Vector3f(static_cast<float>(lua_tonumber(aLuaStack, 3)),
					static_cast<float>(lua_tonumber(aLuaStack, 4)),
					static_cast<float>(lua_tonumber(aLuaStack, 5))));

				return 0;
			}));
		}
	};
	void EngineScriptRegistration::Register()
	{
		GameObjectReg::RegisterFunctions();
		PrefabReg::RegisterFunctions();
		SceneReg::RegisterFunctions();
	}

}

