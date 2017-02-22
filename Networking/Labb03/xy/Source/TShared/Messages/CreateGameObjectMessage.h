#pragma once
#include "GameCode\GameObjectTypes.h"
#include "NetMessage.h"


class CreateGameObjectMessage : public NetMessage
{
public:
	CreateGameObjectMessage();
	~CreateGameObjectMessage();

	GameObjectTypes myType;
	unsigned short myID;

protected:
	virtual void DoSerialize(StreamType & aStreamType) override;


	virtual void DoDeSerialize(StreamType & aStreamType) override;

};
