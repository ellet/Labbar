#pragma once
#include "NetMessage.h"

class ChatNetMessage : public NetMessage
{
public:
	ChatNetMessage();
	~ChatNetMessage();

	const std::string & GetSpeaker() const { return mySpeakerName; }
	void SetSpeaker(const std::string & aName) { mySpeakerName = aName; };

	const std::string & GetChatMessage() const { return myMessage; }
	void SetChatMessage(const std::string & aMessage) { myMessage = aMessage; };

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;
	virtual void DoDeSerialize(StreamType & aStreamType) override;

private:
	std::string mySpeakerName;
	std::string myMessage;
};

