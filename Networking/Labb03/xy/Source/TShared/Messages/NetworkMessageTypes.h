#pragma once

enum class NetworkMessageTypes : char
{
	eSyncGameObject,
	ePing,
	eDisconnect,
	eScore,

	
	eMessage,
	eInputMessage,
	
	
	
	
	eIMPORTANTCUTTOF,
	eGameStateMessage,
	eDummyCreate,
	eCreationMessage,
	eConnection,
	
	enumLength
};

//inline bool operator>(const NetworkMessageTypes aLeft, const NetworkMessageTypes aRight)
//{
//	return  static_cast<char>(aLeft) > static_cast<char>(aRight);
//}
//
//inline bool operator<(const NetworkMessageTypes aLeft, const NetworkMessageTypes aRight)
//{
//	return  static_cast<char>(aLeft) < static_cast<char>(aRight);
//}
