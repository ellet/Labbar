#pragma once
#include "Manager\NetMessageManager.h"
#include "GameCodeNetMessage.h"

class NetMessage;

class NetworkCallback
{
public:
	virtual ~NetworkCallback()
	{}

	virtual void Connect(const std::string & aIp, const std::string & aName) = 0;
	virtual void SendMesseageFromWorld(NetMessage & aMessageToSend) = 0;
	virtual void TranslateComponentMessage(CComponentMessageOnInput & aMessageToConvert);
	virtual void BroadCastMessageFromWorld(NetMessage & aMessageToBroadCast);

	NetMessageManager myMessageManager;
};

inline void NetworkCallback::TranslateComponentMessage(CComponentMessageOnInput & aMessageToConvert)
{
	GameCodeNetMessage gameMessage = myMessageManager.CreateMessage<GameCodeNetMessage>();
	gameMessage.myGameMessage = aMessageToConvert;

	SendMesseageFromWorld(gameMessage);
}

inline void NetworkCallback::BroadCastMessageFromWorld(NetMessage & aMessageToBroadCast)
{
	Error("BroadCast not implemented");
}
