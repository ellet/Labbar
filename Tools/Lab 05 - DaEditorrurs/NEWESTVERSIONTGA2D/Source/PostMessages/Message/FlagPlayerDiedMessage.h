#pragma once
#include "RecieverTypes.h"
#include "BaseMessage.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct FlagPlayerDiedMessage : public BaseMessage
{
	FlagPlayerDiedMessage(const RecieverTypes aType) : BaseMessage(aType)
	{}
	virtual ~FlagPlayerDiedMessage()
	{}
};
#pragma warning (pop)