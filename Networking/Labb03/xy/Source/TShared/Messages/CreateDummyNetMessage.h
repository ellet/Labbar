#pragma once
#include "GameCode\GameObjectTypes.h"
#include "ImportantNetMessage.h"


class CreateDummyNetMessage : public ImportantNetMessage
{
public:
	CreateDummyNetMessage();
	~CreateDummyNetMessage();

	GameObjectTypes myObjectType;
	unsigned short myGameObjectID;


protected:
	virtual void DoImporantSerialize(StreamType & aStreamType) override;
	virtual void DoImporantDeSerialize(StreamType & aStreamType) override;

};

