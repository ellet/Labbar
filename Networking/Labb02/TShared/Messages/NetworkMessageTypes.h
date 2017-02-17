#pragma once

enum class NetworkMessageTypes : char
{
	ePing,
	eConnection,
	eMessage,
	eDisconnect,
	enumLength
};