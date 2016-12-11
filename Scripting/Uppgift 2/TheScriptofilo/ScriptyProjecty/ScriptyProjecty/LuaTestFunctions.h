#pragma once
#include <string>

extern "C" inline int TestFuncton(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	std::cout << "arguemnts: " + std::to_string(args) << std::endl;

	lua_pushnumber(aLuaState, 123);

	return 1;
}

extern "C" inline int PrintFromLua(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	//std::cout << "Print found : " + std::to_string(args) + " number of argument" << std::endl;

	/*for (int n = 1; n <= args; ++n) 
	{
		std::cout << "argument number: " + std::to_string(n) + " is " + lua_tostring(aLuaState, n) << std::endl;
	}*/

	for (int n = 1; n <= args; ++n)
	{
		std::cout << lua_tostring(aLuaState, n);
	}

	std::cout << std::endl;

	lua_pushnumber(aLuaState, 123);

	return 1;
}