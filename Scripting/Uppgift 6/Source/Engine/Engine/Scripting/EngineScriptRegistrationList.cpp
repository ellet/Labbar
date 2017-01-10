#include "stdafx.h"

#include "Engine/Scripting/ScriptHost.h"
#include "EngineScriptRegistrationList.h"
#include "lua.hpp"

namespace SB
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

	// static void stackDump(lua_State *L) {
	// 	int i = lua_gettop(L);
	// 	printf(" ----------------  Stack Dump ----------------\n");
	// 	while (i) {
	// 		int t = lua_type(L, i);
	// 		switch (t) {
	// 		case LUA_TSTRING:
	// 			printf("%d:`%s'\n", i, lua_tostring(L, i));
	// 			break;
	// 		case LUA_TBOOLEAN:
	// 			printf("%d: %s\n", i, lua_toboolean(L, i) ? "true" : "false");
	// 			break;
	// 		case LUA_TNUMBER:
	// 			printf("%d: %g\n", i, lua_tonumber(L, i));
	// 			break;
	// 		default: printf("%d: %s\n", i, lua_typename(L, t)); break;
	// 		}
	// 		i--;
	// 	}
	// 	printf("--------------- Stack Dump Finished ---------------\n");
	// }

	namespace PrefabReg
	{
		static void RegisterFunctions()
		{
			Engine::GetInstance().GetScriptHost().RegisterFunction("SpawnPrefabAtPosition", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				std::string name = lua_tostring(aLuaStack, 2);

				Vector3f pos;
				pos.x = static_cast<float>(lua_tonumber(aLuaStack, 3));
				pos.y = static_cast<float>(lua_tonumber(aLuaStack, 4));
				pos.z = static_cast<float>(lua_tonumber(aLuaStack, 5));

				ObjectPtr newObject = aObject.GetScene().CreateGameObjectFromPrefab(name, pos);
				
				
				newObject->SetPosition(pos);

				return 0;
			}));

			Engine::GetInstance().GetScriptHost().RegisterFunction("SpawnPrefabAtPositionWithRotation", std::function<int(GameObject&, lua_State*)>([](GameObject &aObject, lua_State *aLuaStack) -> int
			{
				std::string name = lua_tostring(aLuaStack, 2);

				Vector3f pos;
				pos.x = static_cast<float>(lua_tonumber(aLuaStack, 3));
				pos.y = static_cast<float>(lua_tonumber(aLuaStack, 4));
				pos.z = static_cast<float>(lua_tonumber(aLuaStack, 5));

				Vector3f rotation;

				rotation.x = static_cast<float>(lua_tonumber(aLuaStack, 6));
				rotation.y = static_cast<float>(lua_tonumber(aLuaStack, 8));
				rotation.z = static_cast<float>(lua_tonumber(aLuaStack, 8));

				ObjectPtr newObject = aObject.GetScene().CreateGameObjectFromPrefab(name, pos);

				//newObject->GetRotation().RotateAroundLocalX(DEGREES_TO_RADIANSF(90));
				newObject->GetRotation().RotateAroundWorldX(DEGREES_TO_RADIANSF(rotation.x));
				newObject->GetRotation().RotateAroundWorldY(DEGREES_TO_RADIANSF(rotation.y + 180.f));
				//newObject->GetRotation().RotateAroundWorldZ(DEGREES_TO_RADIANSF(rotation.z));

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

