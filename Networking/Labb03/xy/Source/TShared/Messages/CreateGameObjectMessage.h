#pragma once
#include "GameCode\GameObjectTypes.h"
#include "ImportantNetMessage.h"



class CreateGameObjectMessage : public ImportantNetMessage
{
public:
	CreateGameObjectMessage();
	~CreateGameObjectMessage();

	GameObjectTypes myType;
	unsigned short myID;

protected:
	virtual void DoImporantSerialize(StreamType & aStreamType) override;


	virtual void DoImporantDeSerialize(StreamType & aStreamType) override;

};
