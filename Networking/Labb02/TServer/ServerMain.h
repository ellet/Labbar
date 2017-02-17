#pragma once
#include <CommonNetworkIncludes.h>
#include "Messages\Manager\NetMessageManager.h"

class PingNetMessage;
class ConnectNetMessage;
class ChatNetMessage;
class DisconnectNetMessage;

struct ClientData
{
	sockaddr_in AddressInformation;
	std::string ClientName;
	SB::Stopwatch ConnectionTimer;
};

class CServerMain
{
public:
	CServerMain();
	~CServerMain();

	bool IsRunning() const { return true; }

	void Update();

	void StartServer();
	void ServerShutdown();

private:
	void UpdateClients();
	unsigned short AddClient(const std::string & aClientName, const sockaddr_in & aClientData);
	void RemoveClient(unsigned short aClientIndex, const std::string & aLeaveReason = "");

	unsigned short GetFreeIndex();
	void ReturnIndex(const unsigned short aIndexToReturn);
	void SetupIndexes();

	void HandleMessage(const ConnectNetMessage & recievedConnectionMessage, const sockaddr_in & aClientData);
	void HandleMessage(const PingNetMessage & recievedPingMessage);
	void HandleMessage(const ChatNetMessage & recievedChatMessage);
	void HandleMessage(const DisconnectNetMessage & recievedChatMessage);
	
	void PrintServerMessage(const std::string & aMessage) const;
	void CheckRecievedMessages();

	void PrintServerAddress() const;

	void ServerBroadcast(const std::string & aBroadcastMessage, const unsigned short aExcludeIndex = 0);
	void BroadcastMessage(NetMessage & aMessageToSend, const unsigned short sendFromIndex);
	void SendNetMessage(NetMessage & aMessageToSend);

	std::unordered_map<unsigned short, ClientData> myConnectedClients;

	SOCKET mySocket;
	
	struct sockaddr_in myServerData;

	std::vector<unsigned short> myFreeIndexes;

	NetMessageManager myMessageManager;
};

