#pragma once

struct LuaNodeDesc
{
	lua_State * LuaState;
	std::string FilePath;
	unsigned short InternalID;
	LONGLONG NodeID;
};

class LuaNode
{
public:
	LuaNode();
	~LuaNode();

	void Init(const LuaNodeDesc & aSetupData);

	lua_State * GetLuaState() const;
	const std::string & GetFilePath() const;
	unsigned short GetInternalID() const;
	LONGLONG GetNodeID() const;

private:
	lua_State * myLuaState;
	std::string myFilePath;
	unsigned short myInternalID;
	LONGLONG myNodeID;
};

