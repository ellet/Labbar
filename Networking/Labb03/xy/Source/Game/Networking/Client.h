#pragma once
#include "Messages\Manager\NetMessageManager.h"
#include "ConsoleInputHandler.h"
#include <CommonNetworkIncludes.h>
#include "Messages/NetworkCallback.h"


class PingNetMessage;
class ConnectNetMessage;
class ChatNetMessage;
class CGameWorld;

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

private:
	void RecieveMessages();

	void SendMessage(NetMessage & aMessageToSend);

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

