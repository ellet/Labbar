#include "LuaNode.h"



LuaNode::LuaNode()
{
}


LuaNode::~LuaNode()
{
}

void LuaNode::Init(const LuaNodeDesc & aSetupData)
{
	myFilePath = aSetupData.FilePath;
	myInternalID = aSetupData.InternalID;
	myLuaState = aSetupData.LuaState;
	myNodeID = aSetupData.NodeID;
}

lua_State * LuaNode::GetLuaState() const
{
	return myLuaState;
}

const std::string & LuaNode::GetFilePath() const
{
	return myFilePath;
}

unsigned short LuaNode::GetInternalID() const
{
	return myInternalID;
}

LONGLONG LuaNode::GetNodeID() const
{
	return myNodeID;
}

