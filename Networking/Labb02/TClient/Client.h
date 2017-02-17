#pragma once
#include "Messages\Manager\NetMessageManager.h"
#include "ConsoleInputHandler.h"

class PingNetMessage;
class ConnectNetMessage;
class ChatNetMessage;

class Client
{
public:
	Client();
	~Client();

	void Startup();
	void Shutdown();

	void Update();

	bool IsRunning() const { return !myShouldShutDown; }

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
	bool myIsConnected;
	bool myShouldShutDown;

	SOCKET mySocket;

	NetMessageManager myMessageManager;

	ConsoleInputHandler myInput;

	std::string myClientName;
	std::string myServerIP;
};

