#include "stdafx.h"
#include "NetMessageManager.h"
#include "..\NetMessage.h"



NetMessageManager::NetMessageManager()
{

}

NetMessageManager::~NetMessageManager()
{

}

void NetMessageManager::SetUserID(const unsigned short aUserID)
{
	myID = aUserID;
}

unsigned short NetMessageManager::GetUserID() const
{
	return myID;
}

void NetMessageManager::SetTargetID(const unsigned short aTargetID)
{
	myTargetID = aTargetID;
}

void NetMessageManager::SetupBaseMessage(NetMessage & aMessageToSetup)
{
	aMessageToSetup.mySenderID = myID;
	aMessageToSetup.myTargetID = myTargetID;
	aMessageToSetup.myTimeStamp = static_cast<unsigned int>( std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

NetworkMessageTypes NetMessageManager::GetMessageType(char * buf) const
{
	return static_cast<NetworkMessageTypes>(buf[0]);
}

void NetMessageManager::UpdateBaseMessage(NetMessage & aMessageToSetup)
{
	SetupBaseMessage(aMessageToSetup);
}
