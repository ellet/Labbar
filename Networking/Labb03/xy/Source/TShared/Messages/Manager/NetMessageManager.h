#pragma once

class NetMessage;

class NetMessageManager
{
public:
	NetMessageManager();
	~NetMessageManager();

	template <typename TMessageType>
	TMessageType CreateMessage();

	void SetUserID(const unsigned short aUserID);
	unsigned short GetUserID() const;

	void SetTargetID(const unsigned short aTargetID);

	NetworkMessageTypes GetMessageType(char * buf) const;

	void UpdateBaseMessage(NetMessage & aMessageToSetup);

private:
	void SetupBaseMessage(NetMessage & aMessageToSetup);

	unsigned short myID;
	unsigned short myTargetID;
	
};

template <typename TMessageType>
TMessageType NetMessageManager::CreateMessage()
{
	TMessageType newMessage;

	SetupBaseMessage(newMessage);

	return newMessage;
}

