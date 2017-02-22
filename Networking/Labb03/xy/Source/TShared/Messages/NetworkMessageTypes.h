#pragma once

enum class NetworkMessageTypes : char
{
	eSyncGameObject,
	ePing,
	eDisconnect,

	eConnection,
	eMessage,
	eInputMessage,
	eCreationMessage,
	
	
	enumLength
};
