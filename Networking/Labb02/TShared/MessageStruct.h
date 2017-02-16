#pragma once
#include <string>

enum class MessageType
{
	ePing,
	eConnect,
	eMessage
};

struct NetworkMessage
{
	MessageType Type;
	char Message[256];
};