#pragma once

#include <string>
#include <vector>
#include <unordered_map>


struct LuaNodeDesc
{
	lua_State * LuaState;
	std::string FilePath;
	size_t InternalID;
	long long NodeID;
	std::vector<std::string> * Events;
};

class LuaNode
{
public:
	LuaNode();
	~LuaNode();

	void Init(const LuaNodeDesc & aSetupData);

	void CloseFile();

	void RegisterEventCallback(const std::string & aEventName, const std::string & aCallbackFunctionName);
	const std::string & GetEventFunction(const std::string & aEventName);

	lua_State * GetLuaState() const;
	const std::string & GetFilePath() const;
	size_t GetInternalID() const;
	long long GetNodeID() const;

private:
	std::unordered_map<std::string, std::string> myEvents;

	lua_State * myLuaState;
	std::string myFilePath;
	size_t myInternalID;
	long long myNodeID;
};

