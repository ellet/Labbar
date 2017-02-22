#include "stdafx.h"
#include "ServerMain.h"
#include "..\TShared\Messages\PingNetMessage.h"
#include "..\TShared\Messages\ConnectNetMessage.h"
#include "..\TShared\Messages\ChatNetMessage.h"
#include "..\TShared\Messages\DisconnectNetMessage.h"
#include "ServerWorld.h"
#include "..\TShared\Messages\GameCodeNetMessage.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512  //Max length of buffer
#define PORT 23073   //The port on which to listen for incoming data

const unsigned short MaxConnections = 25;


CServerMain::CServerMain()
{
	mySocket = 0;

	SetupIndexes();
	myTimerManager.CreateTimer();
}


CServerMain::~CServerMain()
{
}

void CServerMain::Update()
{
	CheckRecievedMessages();
	UpdateClients();


	const float timeStep = 1.f / 60.f;
	//const float deltaTime = (float)myTimerManager.GetTimer(0).GetDeltaTime().GetMicroseconds() / 1000000.f;
	const float deltaTime = myDeltaTimeTimer.GetElapsedTime().InSeconds();
	myDeltaTimeTimer.Restart();
	static float timerCounter = 0;
	timerCounter += deltaTime;

	while (timerCounter >= timeStep)
	{
		myGameWorld->Update(timeStep);
		timerCounter -= timeStep;
	}
}

void CServerMain::StartServer()
{
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
	
	//Prepare the sockaddr_in structure
	myServerData.sin_family = AF_INET;
	myServerData.sin_addr.s_addr = INADDR_ANY;
	myServerData.sin_port = htons(PORT);
	

	//Bind
	ProgressMessage("Binding Socket...");
	if (bind(mySocket, (struct sockaddr *)&myServerData, sizeof(myServerData)) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("Bind failed with error code: " + std::to_string(WSAGetLastError()));
	}

	std::string aip = inet_ntoa(myServerData.sin_addr);

	ProgressMessage("Bind done");

	myMessageManager.SetUserID(globalServerID);

	PrintServerAddress();
	CreateWorld();

	PrintServerMessage("---Server is ready for connections---");
}

void CServerMain::ServerShutdown()
{
	closesocket(mySocket);
	WSACleanup();
}

void CServerMain::Connect(const std::string & aIp, const std::string & aName)
{
	
}

void CServerMain::SendMesseageFromWorld(NetMessage & aMessageToSend)
{
	SendNetMessage(aMessageToSend);
}

void CServerMain::BroadCastMessageFromWorld(NetMessage & aMessageToBroadCast)
{
	BroadcastMessage(aMessageToBroadCast, 0);
}


void CServerMain::CreateWorld()
{
	PrintServerMessage("Creating World");

	myGameWorld = std::make_unique<ServerWorld>();
	myGameWorld->SetNetworkCallback(*this);
	myGameWorld->Init();

	PrintServerMessage("World Created");
}

void CServerMain::UpdateClients()
{
	std::unordered_map<unsigned short, ClientData>::iterator iClient = myConnectedClients.begin();

	std::vector<unsigned int> indexesToRemove;

	for (; iClient != myConnectedClients.end(); ++iClient)
	{
		if (iClient->second.ConnectionTimer.GetElapsedTime() >= 10.f)
		{
			indexesToRemove.push_back(iClient->first);
		}
	}

	for (unsigned short iClientsToRemove = 0; iClientsToRemove < indexesToRemove.size(); ++iClientsToRemove)
	{
		RemoveClient(indexesToRemove[iClientsToRemove], " timed out");
	}
}

unsigned short CServerMain::AddClient(const std::string & aClientName, const sockaddr_in & aClientData)
{
	unsigned short newClientIndex = GetFreeIndex();
	
	if (myConnectedClients.find(newClientIndex) != myConnectedClients.end())
	{
		SomethingWentWrongMessage("Server tried to add new index: " + std::to_string(newClientIndex) + " but it was already occupied");
	}
	
	ClientData newClient;

	newClient.AddressInformation = aClientData;
	newClient.ClientName = aClientName;

	myConnectedClients[newClientIndex] = newClient;


	myConnectedClients[newClientIndex].ConnectionTimer.Restart();
	return newClientIndex;
}


void CServerMain::RemoveClient(unsigned short aClientIndex, const std::string & aLeaveReason /*= ""*/)
{
	ReturnIndex(aClientIndex);

	std::string clientName = myConnectedClients[aClientIndex].ClientName;

	myConnectedClients.erase(myConnectedClients.find(aClientIndex));

	PrintServerMessage(clientName + " has disconnected - " + aLeaveReason);
	ServerBroadcast(clientName + " has disconnected - " + aLeaveReason);
}

unsigned short CServerMain::GetFreeIndex()
{
	if (myFreeIndexes.size() > 0)
	{
		unsigned short freeIndex = myFreeIndexes.back();
		myFreeIndexes.erase(myFreeIndexes.end() - 1);

		return freeIndex;
	}
	else
	{
		PrintServerMessage("Server is full");
		return 0;
	}
}

void CServerMain::ReturnIndex(const unsigned short aIndexToReturn)
{
	myFreeIndexes.push_back(aIndexToReturn);
}

void CServerMain::SetupIndexes()
{
	for (unsigned short iIndex = 1; iIndex <= MaxConnections; ++iIndex)
	{
		myFreeIndexes.push_back(iIndex);
	}
}

void CServerMain::HandleMessage(const ConnectNetMessage & recievedConnectionMessage, const sockaddr_in & aClientData)
{
	const unsigned short NewClientIndex = AddClient(recievedConnectionMessage.GetClientName(), aClientData);

	myMessageManager.SetTargetID(NewClientIndex);

	ConnectNetMessage responseMessage = myMessageManager.CreateMessage<ConnectNetMessage>();
	PrintServerMessage(recievedConnectionMessage.GetClientName() + " has connected to server and was assigned ID: " + std::to_string(responseMessage.GetTargetID()));
	
	responseMessage.SetUserName("SERVER");

	SendNetMessage(responseMessage);
	ServerBroadcast(recievedConnectionMessage.GetClientName() + " has connected", NewClientIndex);
	myGameWorld->OnConnect(NewClientIndex);
}

void CServerMain::HandleMessage(const PingNetMessage & recievedPingMessage)
{
	const unsigned short senderID = recievedPingMessage.GetSenderID();

	PrintServerMessage("Ping recieved from client " + myConnectedClients[senderID].ClientName + " with ID: " + std::to_string(senderID));

	myMessageManager.SetTargetID(senderID);
	
	PingNetMessage responseMessage = myMessageManager.CreateMessage<PingNetMessage>();
	responseMessage.PackMessage();

	SendNetMessage(responseMessage);

	myConnectedClients[senderID].ConnectionTimer.Restart();
}


void CServerMain::HandleMessage(const ChatNetMessage & recievedChatMessage)
{
	PrintServerMessage("Server recieved chat message from " + myConnectedClients[recievedChatMessage.GetSenderID()].ClientName);

	ChatNetMessage responseMessage = recievedChatMessage;

	BroadcastMessage(responseMessage, recievedChatMessage.GetSenderID());
}

void CServerMain::HandleMessage(const DisconnectNetMessage & recievedChatMessage)
{
	PrintServerMessage("Recieved disconnect message from " + myConnectedClients[recievedChatMessage.GetSenderID()].ClientName);

	RemoveClient(recievedChatMessage.GetSenderID(), "user quit");
}

void CServerMain::PrintServerMessage(const std::string & aMessage) const
{
	std::cout << aMessage << std::endl;
}

void CServerMain::CheckRecievedMessages()
{
	//clear the buffer by filling null, it might have previously received data
	char buf[BUFLEN];
	int recieveLengthOfMessage;

	memset(buf, '\0', BUFLEN);
	
	sockaddr_in clientMessageData;
	int sizeOfMessageData = sizeof(clientMessageData);

	//try to receive some data, this is a blocking call
	recieveLengthOfMessage = recvfrom(mySocket, buf, BUFLEN, 0, (struct sockaddr *) &clientMessageData, &sizeOfMessageData);
	
	if (recieveLengthOfMessage == SOCKET_ERROR)
	{
		const int SocketError = WSAGetLastError();
	
		if (SocketError == 10054)
		{
			PrintServerMessage("Socket not responding");
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
			recievedMessage.UnPackMessage(buf, recieveLengthOfMessage);

			HandleMessage(recievedMessage, clientMessageData);
		}
		break;

		case NetworkMessageTypes::ePing:
		{
			PingNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, recieveLengthOfMessage);

			HandleMessage(recievedMessage);
		}
		break;
		
		case NetworkMessageTypes::eMessage:
		{
			ChatNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, recieveLengthOfMessage);

			HandleMessage(recievedMessage);
		}
		break;

		case NetworkMessageTypes::eDisconnect:
		{
			DisconnectNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, recieveLengthOfMessage);

			HandleMessage(recievedMessage);
		}

		case NetworkMessageTypes::eInputMessage:
		{
			GameCodeNetMessage recievedMessage;
			recievedMessage.UnPackMessage(buf, recieveLengthOfMessage);

			myGameWorld->HandleInputMessage(recievedMessage);
		}
		break;

		default:
			SomethingWentWrongMessage("server could not find message type");
			break;
		}
	}
}

void CServerMain::PrintServerAddress() const
{
	char buffer[1024];
	gethostname(buffer, sizeof(buffer));

	struct hostent *phe = gethostbyname(buffer);
	if (phe == 0) {
		std::cout << "Yow! Bad host lookup." << std::endl;
		//return 1;
	}


	struct in_addr addr;
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	PrintServerMessage("Server address is: " + std::string(inet_ntoa(addr)));
}

void CServerMain::ServerBroadcast(const std::string & aBroadcastMessage, const unsigned short aExcludeIndex /*= 0*/)
{
	ChatNetMessage newBroadCast = myMessageManager.CreateMessage<ChatNetMessage>();
	newBroadCast.SetSpeaker("ServerBroadcast");
	newBroadCast.SetChatMessage(aBroadcastMessage);

	BroadcastMessage(newBroadCast, aExcludeIndex);
}

void CServerMain::BroadcastMessage(NetMessage & aMessageToSend, const unsigned short sendFromIndex)
{
	std::unordered_map<unsigned short, ClientData>::iterator iClient = myConnectedClients.begin();

	for (; iClient != myConnectedClients.end(); ++iClient)
	{
		if (iClient->first != sendFromIndex)
		{
			myMessageManager.SetTargetID(iClient->first);
			myMessageManager.UpdateBaseMessage(aMessageToSend);
			SendNetMessage(aMessageToSend);
		}
	}
}

void CServerMain::SendNetMessage(NetMessage & aMessageToSend)
{
	aMessageToSend.PackMessage();

	const unsigned short clientIndex = aMessageToSend.GetTargetID();

	sockaddr_in & clientMessageData = myConnectedClients[clientIndex].AddressInformation;
	int sizeOfMessageData = sizeof(clientMessageData);
	if (sendto(mySocket, &aMessageToSend.myStream[0], aMessageToSend.myStream.size(), 0, (struct sockaddr*) &clientMessageData, sizeOfMessageData) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("failed to respond connection with error code: " + std::to_string(WSAGetLastError()));
	}
}

