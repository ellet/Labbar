#pragma once
#include "Messages\Manager\NetMessageManager.h"
#include "ConsoleInputHandler.h"
#include <CommonNetworkIncludes.h>
#include "Messages/NetworkCallback.h"
#include "ImportantMessageData.h"


class PingNetMessage;
class ConnectNetMessage;
class ChatNetMessage;
class CGameWorld;
class ImportantNetMessage;

class Client : public NetworkCallback
{
public:
	Client();
	~Client();

	void Startup();
	void ConnectToServer(const std::string & aClientName, const std::string & aIPaddress);

	void Shutdown();

	void Update();

	bool IsRunning() const { return !myShouldShutDown; }

	void SetGameWorld(CGameWorld & aGameWorld);


	virtual void Connect(const std::string & aIp, const std::string & aName) override;


	virtual void SendMesseageFromWorld(NetMessage & aMessageToSend) override;


	virtual void SendMesseageFromWorld(ImportantNetMessage & aMessageToSend) override;

private:
	bool HandleImportantMessage(ImportantNetMessage & aImportantMessage);
	void UpdateImportantMessages();
	unsigned short GetNewImportantMessageID();

	void RecieveMessages();

	void SendNetMessage(NetMessage & aMessageToSend);
	void SendNetMessage(ImportantNetMessage & aMessage);
	void SendNetMessage(StreamType & message);

	void HandleMessage(const PingNetMessage & aPingMessage);
	void HandleMessage(const ConnectNetMessage & aConnectionMessage);
	void HandleMessage(const ChatNetMessage & aNetMessage);

	void PingServer();
	void PrintClientMessage(const std::string & aMessage);

	void HandleCommand(const std::string & aCommand);
	void TurnOffClient();
	void PrintHelp();

	
	
	void UserClientSetup();
	void ConnectToServer();

	std::unordered_map<unsigned short, ImportantMessageData> myImportantMessages;
	std::unordered_map<unsigned short, SB::Stopwatch> myRecievedMessages;
	unsigned short myMessageCounter;

	SB::Stopwatch myPingTimer;
	SB::Stopwatch myConnectionTimer;

	struct sockaddr_in myServerData;

	int myServerDataLength;

	bool myIsSetup;
	bool myIsConnected;
	bool myShouldShutDown;

	SOCKET mySocket;

	//ConsoleInputHandler myInput;

	std::string myClientName;
	std::string myServerIP;

	CGameWorld * myGameWorld;
};

