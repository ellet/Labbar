#pragma once
#include "Manager\NetMessageManager.h"
#include "GameCodeNetMessage.h"

class NetMessage;
class ImportantNetMessage;

class NetworkCallback
{
public:
	virtual ~NetworkCallback()
	{}

	virtual void Connect(const std::string & aIp, const std::string & aName) = 0;
	virtual void SendMesseageFromWorld(NetMessage & aMessageToSend) = 0;
	virtual void SendMesseageFromWorld(ImportantNetMessage & aMessageToSend) = 0;
	virtual void TranslateComponentMessage(CComponentMessageOnInput & aMessageToConvert);
	virtual void BroadCastMessageFromWorld(NetMessage & aMessageToBroadCast);
	virtual void BroadCastMessageFromWorld(ImportantNetMessage & aMessageToBroadCast);

	unsigned short GetUserID() const;

	NetMessageManager myMessageManager;
};

inline void NetworkCallback::TranslateComponentMessage(CComponentMessageOnInput & aMessageToConvert)
{
	GameCodeNetMessage gameMessage = myMessageManager.CreateMessage<GameCodeNetMessage>();
	gameMessage.myGameMessage = aMessageToConvert;

	SendMesseageFromWorld(gameMessage);
}

inline void NetworkCallback::BroadCastMessageFromWorld(NetMessage & /*aMessageToBroadCast*/)
{
	Error("BroadCast not implemented");
}

inline void NetworkCallback::BroadCastMessageFromWorld(ImportantNetMessage & /*aMessageToBroadCast*/)
{
	Error("BroadCast not implemented");
}

inline unsigned short NetworkCallback::GetUserID() const
{
	return myMessageManager.GetUserID();
}

