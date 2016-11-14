#include "stdafx.h"

#include "GameScriptRegistrationList.h"
#include <Engine\Scripting\ScriptHost.h>
#include "lua.hpp"
#include "Game\Objective\ObjectiveComponent.h"
#include "Game\Player\PlayerShootComponent.h"
#include "..\Objective\ObjectiveHandlerComponent.h"
#include "Game/GenericGameMessages.h"
#include <functional>

#pragma warning (disable : 4702)
namespace ObjectiveReg
{
	void RegisterFunctions()
	{
		SB::ScriptHost &scriptHost = SB::Engine::GetInstance().GetScriptHost();
		scriptHost.RegisterFunction("ObjectiveSetCounter", std::function<int(SB::GameObject&, lua_State*) >([](SB::GameObject &aObject, lua_State *aLuaStack) -> int
		{
			const char * componentToLookFor = lua_tostring(aLuaStack, 2);
			int counter = static_cast<int> (lua_tointeger(aLuaStack, 3));

			for (unsigned short i = 0; i < aObject.GetComponentCount<ObjectiveComponent>(); ++i)
			{
				if (aObject.GetComponent<ObjectiveComponent>(i)->GetIdentity() == componentToLookFor)
				{
					aObject.GetComponent<ObjectiveComponent>(i)->SetCounter(static_cast<unsigned short>(counter));
					return 0;
				}
			}

			luaL_error(aLuaStack, "Could not find objective with name: %s!", componentToLookFor);
			return 0;
		}));
		scriptHost.RegisterFunction("ObjectiveIncrementCounter", std::function<int(SB::GameObject&, lua_State*) >([](SB::GameObject &aObject, lua_State *aLuaStack) -> int
		{
			const char * componentToLookFor = lua_tostring(aLuaStack, 2);
			int incrementValue = static_cast<int> (lua_tointeger(aLuaStack, 3));

			for (unsigned short i = 0; i < aObject.GetComponentCount<ObjectiveComponent>(); ++i)
			{
				if (aObject.GetComponent<ObjectiveComponent>(i)->GetIdentity() == componentToLookFor)
				{
					aObject.GetComponent<ObjectiveComponent>(i)->IncrementCounter(static_cast<unsigned short>(incrementValue));
					return 0;
				}
			}

			luaL_error(aLuaStack, "Could not find objective with name: %s!", componentToLookFor);
			return 0;
		}));
		scriptHost.RegisterFunction("ObjectiveDecrementCounter", std::function<int(SB::GameObject&, lua_State*) >([](SB::GameObject &aObject, lua_State *aLuaStack) -> int
		{
			const char * componentToLookFor = lua_tostring(aLuaStack, 2);
			int decrementValue = static_cast<int> (lua_tointeger(aLuaStack, 3));

			for (unsigned short i = 0; i < aObject.GetComponentCount<ObjectiveComponent>(); ++i)
			{
				if (aObject.GetComponent<ObjectiveComponent>(i)->GetIdentity() == componentToLookFor)
				{
					aObject.GetComponent<ObjectiveComponent>(i)->IncrementCounter(static_cast<unsigned short>(decrementValue));
					return 0;
				}
			}

			luaL_error(aLuaStack, "Could not find objective with name: %s!", componentToLookFor);
			return 0;
		}));
		scriptHost.RegisterFunction("ActivateObjective", std::function<int(SB::GameObject&, lua_State*) >([](SB::GameObject &aObject, lua_State *aLuaStack) -> int
		{
			const char * objectiveToBeActivated = lua_tostring(aLuaStack, 2);
			SB::ObjectPtr sceneHandler = aObject.GetScene().FindObject("SceneHandler");
			if (sceneHandler != nullptr)
			{

				SB::ComponentPtr<ObjectiveHandlerComponent> objectiveHandler = sceneHandler->GetComponent<ObjectiveHandlerComponent>();
				objectiveHandler->ActivateObjective(objectiveToBeActivated);
			}

			return 0;
		}));
	}

}

namespace PlayerShootReg
{
	void RegisterFunctions()
	{
		SB::Engine::GetInstance().GetScriptHost().RegisterFunction("GetTimesFired", std::function<int(SB::GameObject&, lua_State*)>([](SB::GameObject &aObject, lua_State *aLuaStack) -> int
		{
			lua_pushnumber(aLuaStack, aObject.GetComponent<PlayerShootComponent>()->GetTimesFired());

			return 1;
		}));
	}
}

namespace Level
{
	void RegisterFunctions()
	{
		SB::Engine::GetInstance().GetScriptHost().RegisterFunction("LevelCleared", std::function<int(SB::GameObject&, lua_State*)>([](SB::GameObject &aObject, lua_State *aLuaStack) -> int
		{
			//Error("CALLED LEVELCLEARED");
			SB::PostMaster::Post(LevelClearedMessage()); //LEVEL CLEAREEED
			return 1;
		}));
	}
}


void GameScriptRegistration::Register()
{
	ObjectiveReg::RegisterFunctions();
	PlayerShootReg::RegisterFunctions();
	Level::RegisterFunctions();
	//GameObject::RegisterScriptFunctions();
}


#pragma warning (default : 4702)
