#pragma once
#include "CU/PostMaster/ReceiverTypes.h"
#pragma warning  (push)
#pragma warning(disable : 4512)
struct BaseMessage
{
	BaseMessage(const ReceiverTypes aType) : myType(aType)
	{
	}
	virtual ~BaseMessage()
	{}

	const ReceiverTypes myType;
};
#pragma warning (pop)