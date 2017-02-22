#include "stdafx.h"
#include "Client.h"
#include "Messages\ConnectNetMessage.h"
#include "Messages\PingNetMessage.h"
#include "Messages\ChatNetMessage.h"
#include "Messages\DisconnectNetMessage.h"
#include "..\GameWorld.h"
#include "Messages\SyncGameObjectMessage.h"
#include "Messages\CreateGameObjectMessage.h"

#pragma comment(lib,"ws2_32.lib")

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 23073   //The port on which to listen for incoming data

Client::Client()
{
	myIsConnected = false;

	myServerDataLength = sizeof(myServerData);

	myShouldShutDown = false;
}


Client::~Client()
{
}

void Client::Startup()
{
	myIsSetup = false;
	//Initialise winsock
	std::cout << "Initialising Winsock..." << std::endl;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		SomethingWentWrongMessage("Failed. Error Code : " + std::to_string(WSAGetLastError()));
	}
	ProgressMessage("Winsock Initialised.");

	//Create a socket
	if ((mySocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		SomethingWentWrongMessage("Could not create socket: " + std::to_string(WSAGetLastError()));
	}
	ProgressMessage("Socket Created.");

	ProgressMessage("Unblock Socket");
	u_long blocking = 1;
	ioctlsocket(mySocket, FIONBIO, &blocking);

	//setup address structure
	

	


	//UserClientSetup();

	

	
}

void Client::Shutdown()
{
	//myInput.Stop();
	PrintClientMessage("Shutting down client");
	std::system("pause");
	
	closesocket(mySocket);
	WSACleanup();
}

void Client::Update()
{
	if (myIsSetup == false)
	{
		return;
	}

	RecieveMessages();

	if (myIsConnected == true)
	{
		if (myConnectionTimer.GetElapsedTime().InSeconds() >= 10.f)
		{
			PrintClientMessage("Connection to server timed out");
			myIsConnected = false;
		}
		else if (myPingTimer.GetElapsedTime().InSeconds() >= 1.f)
		{
			PingServer();
			myPingTimer.Restart();
		}

		/*std::string inputString;
		if (myInput.GetInputString(inputString) == true)
		{
			if (inputString[0] == '#')
			{
				HandleCommand(inputString);
			}
			else
			{

				ChatNetMessage chatMessage = myMessageManager.CreateMessage<ChatNetMessage>();
				chatMessage.SetSpeaker(myClientName);
				chatMessage.SetChatMessage(inputString);

				SendMessage(chatMessage);
			}
		}*/
	}
	else
	{
		if (myConnectionTimer.GetElapsedTime() > 3.f && myShouldShutDown == false)
		{
			PrintClientMessage("trying to reconnect to server...");
			ConnectToServer();
		}
	}
}


void Client::SetGameWorld(CGameWorld & aGameWorld)
{
	myGameWorld = &aGameWorld;
}


void Client::Connect(const std::string & aIp, const std::string & aName)
{
	myClientName = aName;
	myServerIP = aIp;
	myIsSetup = true;

	ConnectToServer();
}

void Client::SendMesseageFromWorld(NetMessage & aMessageToSend)
{
	SendMessage(aMessageToSend);
}


void Client::SendMessage(NetMessage & aMessageToSend)
{
	aMessageToSend.PackMessage();
	if (sendto(mySocket, &aMessageToSend.myStream[0], aMessageToSend.myStream.size(), 0, (struct sockaddr *) &myServerData, myServerDataLength) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("sendto() failed with error code : " + std::to_string(WSAGetLastError()));
	}
}

void Client::RecieveMessages()
{

	char buf[BUFLEN];
	int recieveLengthOfMessage;
	

	memset(buf, '\0', BUFLEN);

	//try to receive some data, this is a blocking call
	recieveLengthOfMessage = recvfrom(mySocket, buf, BUFLEN, 0, (struct sockaddr *) &myServerData, &myServerDataLength);
	unsigned short lenghOfMessage = static_cast<unsigned short>( recieveLengthOfMessage);

	if (recieveLengthOfMessage == SOCKET_ERROR)
	{
		const int SocketError = WSAGetLastError();

		if (SocketError == 10054)
		{
			if (myIsConnected == true)
			{
				PrintClientMessage("Lost Connection to Server");
				myIsConnected = false;
				myMessageManager.SetUserID(0);
			}
		}
		else if (SocketError != 10035)
		{
			SomethingWentWrongMessage("recvfrom() failed with error code : " + std::to_string(SocketError));
		}
	}
	else
	{
		NetworkMessageTypes messageType = myMessageManager.GetMessageType(buf);

		switch (messageType)
		{
		case NetworkMessageTypes::eConnection:
		{
			ConnectNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, lenghOfMessage);

			HandleMessage(recievedMessage);
		}
		break;

		case NetworkMessageTypes::ePing:
		{
			PingNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, lenghOfMessage);

			HandleMessage(recievedMessage);
		}
		break;

		case NetworkMessageTypes::eMessage:
		{
			ChatNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, lenghOfMessage);

			HandleMessage(recievedMessage);
		}
		break;

		case NetworkMessageTypes::eSyncGameObject:
		{
			SyncGameObjectMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, lenghOfMessage);

			myGameWorld->RecieveMessage(recievedMessage);
		}
		break;

		case NetworkMessageTypes::eCreationMessage:
		{
			CreateGameObjectMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, lenghOfMessage);

			myGameWorld->RecieveMessage(recievedMessage);
		}
		break;

		default:
			SomethingWentWrongMessage("Could not find network message type");
			break;
		}
	}
}

void Client::HandleMessage(const PingNetMessage & /*aPingMessage*/)
{
	//PrintClientMessage("Recieved ping message from server with ID: " + std::to_string(aPingMessage.GetSenderID()));
	myConnectionTimer.Restart();
}

void Client::HandleMessage(const ConnectNetMessage & aConnectionMessage)
{
	if (myIsConnected == false)
	{
		PrintClientMessage("Connection to server confirmed");
		PrintClientMessage(myClientName + " was assigned ID: " + std::to_string(aConnectionMessage.GetTargetID()));

		myMessageManager.SetUserID(aConnectionMessage.GetTargetID());

		//PrintClientMessage("type #help to get help");
		//myInput.Start(myClientName);
		myIsConnected = true;
		myConnectionTimer.Restart();
	}
	else
	{
		PrintClientMessage("Client receieved connection message but is already connected to server, message discarded");
	}
}

void Client::HandleMessage(const ChatNetMessage & aNetMessage)
{
	PrintClientMessage("");
	PrintClientMessage(aNetMessage.GetSpeaker() + ": " + aNetMessage.GetChatMessage());
	myConnectionTimer.Restart();
}

void Client::PingServer()
{
	PingNetMessage pingMessage = myMessageManager.CreateMessage<PingNetMessage>();
	pingMessage.PackMessage();

	if (sendto(mySocket, &pingMessage.myStream[0], pingMessage.myStream.size(), 0, (struct sockaddr *) &myServerData, myServerDataLength) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("sendto() failed with error code : " + std::to_string(WSAGetLastError()));
	}
}

void Client::PrintClientMessage(const std::string & aMessage)
{
	std::cout << aMessage << std::endl;
}

void Client::TurnOffClient()
{
	DisconnectNetMessage discMessage = myMessageManager.CreateMessage<DisconnectNetMessage>();
	SendMessage(discMessage);

	myIsConnected = false;
	myShouldShutDown = true;
}

void Client::PrintHelp()
{
	PrintClientMessage("-------------------");
	PrintClientMessage("HELP: ");
	PrintClientMessage("Type #quit to turn of client");
	PrintClientMessage("-------------------");
}

void Client::HandleCommand(const std::string & aCommand)
{
	if (aCommand == "#quit")
	{
		TurnOffClient();
	}
	else if (aCommand == "#help")
	{
		PrintHelp();
	}
	else
	{
		PrintClientMessage("unrecognised command");
	}
}

void Client::UserClientSetup()
{
	std::cout << "Input Server IP: ";
	std::getline(std::cin, myServerIP);
	
	if (myServerIP == "")
	{
		myServerIP = SERVER;
	}
	else if (myServerIP == "l1")
	{
		myServerIP = "10.155.92.108";
	}
	
	std::cout << "Input Client Name: ";
	std::getline(std::cin, myClientName);
	
	if (myClientName == "")
	{
		myClientName = "Bertil";
	}

	PrintClientMessage("Connecting to IP: " + myServerIP);
	PrintClientMessage("Clientname is: " + myClientName);
}

void Client::ConnectToServer()
{
	memset((char *)&myServerData, 0, sizeof(myServerData));
	myServerData.sin_family = AF_INET;
	myServerData.sin_port = htons(PORT);
	myServerData.sin_addr.S_un.S_addr = inet_addr(myServerIP.c_str());

	ConnectNetMessage connectMessage = myMessageManager.CreateMessage<ConnectNetMessage>();
	connectMessage.SetUserName(myClientName);
	connectMessage.PackMessage();

	myIsConnected = false;
	if (sendto(mySocket, &connectMessage.myStream[0], connectMessage.myStream.size(), 0, (struct sockaddr *) &myServerData, myServerDataLength) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("sendto() failed with error code : " + std::to_string(WSAGetLastError()));
	}
	
	myConnectionTimer.Restart();
}

