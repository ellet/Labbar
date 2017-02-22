#pragma once
#include <CommonNetworkIncludes.h>
#include "Messages\Manager\NetMessageManager.h"
#include "..\CommonUtilites\TimerManager.h"
#include "..\TShared\Messages\NetworkCallback.h"
#include "..\TShared\ImportantMessageData.h"

class PingNetMessage;
class ConnectNetMessage;
class ChatNetMessage;
class DisconnectNetMessage;
class ServerWorld;
class ImportantNetMessage;


struct ClientData
{
	sockaddr_in AddressInformation;
	std::string ClientName;
	SB::Stopwatch ConnectionTimer;
	std::unordered_map<unsigned short, SB::Stopwatch> myRecievedMessages;
};

class CServerMain : public NetworkCallback
{
public:
	CServerMain();
	~CServerMain();

	bool IsRunning() const { return true; }

	void Update();

	void StartServer();
	void ServerShutdown();


	virtual void Connect(const std::string & aIp, const std::string & aName) override;
	virtual void SendMesseageFromWorld(NetMessage & aMessageToSend) override;
	virtual void BroadCastMessageFromWorld(NetMessage & aMessageToBroadCast) override;
	virtual void SendMesseageFromWorld(ImportantNetMessage & aMessageToSend) override;
	virtual void BroadCastMessageFromWorld(ImportantNetMessage & aMessageToBroadCast) override;

private:
	bool HandleImportantMessage(ImportantNetMessage & aImportantMessage);
	void UpdateImportantMessages();
	unsigned short GetNewImportantMessageID();

	void CreateWorld();

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
	void BroadcastMessage(ImportantNetMessage & aMessageToSend, const unsigned short sendFromIndex);
	void SendNetMessage(NetMessage & aMessageToSend);
	void SendNetMessage(ImportantNetMessage & aMessage);
	void SendNetMessage(StreamType & message, const unsigned short aUserID);
	void SendNetMessage(StreamType & message, const sockaddr_in & addressTosendTo);

	
	
	std::unordered_map<unsigned int, ImportantMessageData> myImportantMessages;
	
	unsigned short myMessageCounter;

	std::unordered_map<unsigned short, ClientData> myConnectedClients;
	SOCKET mySocket;
	
	sockaddr_in myLatestAddr;
	int myLatestAddrSize;

	struct sockaddr_in myServerData;
	std::vector<unsigned short> myFreeIndexes;

	std::unique_ptr<ServerWorld> myGameWorld;

	CommonUtilities::TimerManager myTimerManager;
	SB::Stopwatch myDeltaTimeTimer;
};

