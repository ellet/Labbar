#include "stdafx.h"
#include "Client.h"
#include "Messages\ConnectNetMessage.h"
#include "Messages\PingNetMessage.h"
#include "Messages\ChatNetMessage.h"
#include "Messages\DisconnectNetMessage.h"

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
	

	


	UserClientSetup();

	memset((char *)&myServerData, 0, sizeof(myServerData));
	myServerData.sin_family = AF_INET;
	myServerData.sin_port = htons(PORT);
	myServerData.sin_addr.S_un.S_addr = inet_addr(myServerIP.c_str());

	

	ConnectToServer();
}

void Client::Shutdown()
{
	myInput.Stop();
	PrintClientMessage("Shutting down client");
	std::system("pause");
	
	closesocket(mySocket);
	WSACleanup();
}

void Client::Update()
{
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

		std::string inputString;
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
		}
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
			recievedMessage.UnPackMessage(buf, recieveLengthOfMessage);

			HandleMessage(recievedMessage);
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

		default:
			SomethingWentWrongMessage("Could not find network type");
			break;
		}
	}
}

void Client::HandleMessage(const PingNetMessage & aPingMessage)
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

		PrintClientMessage("type #help to get help");
		myInput.Start(myClientName);
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

//bool isConnected = true;
//SB::Stopwatch pingTimer;
//
//struct sockaddr_in si_other;
//int s, slen = sizeof(si_other);
//char buf[BUFLEN];
////char message[BUFLEN];
////char * message = "apa";
//
//std::string ServerIPString;
//std::string ClientName;
//
//WSADATA wsa;
//
////Initialise winsock
//printf("\nInitialising Winsock...");
//if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//{
//	printf("Failed. Error Code : %d", WSAGetLastError());
//	//exit(EXIT_FAILURE);
//}
//printf("Initialised.\n");
//
////create socket
//if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
//{
//	printf("socket() failed with error code : %d", WSAGetLastError());
//	//exit(EXIT_FAILURE);
//}
//
//u_long blocking = 1;
//ioctlsocket(s, FIONBIO, &blocking);
//





//
//NetworkMessage messageToSend;
//messageToSend.Type = MessageType::eMessage;
//memcpy(messageToSend.Message, "apa", 4);
//
//std::cout << "Input Server IP" << std::endl;
//
//
//std::cout << "ServerIp is: " << ServerIPString << std::endl;
//std::cout << "Client Name is: " << ClientName << std::endl;
//
//NetworkMessage connectionMessage;
//connectionMessage.Type = MessageType::eConnect;
//memcpy(connectionMessage.Message, ClientName.c_str(), ClientName.length() + 1);
//
//unsigned short pingCounter = 0;
//
//char * message = reinterpret_cast<char*>(&connectionMessage);
//
//if (sendto(s, message, sizeof(messageToSend), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
//{
//	printf("sendto() failed with error code : %d", WSAGetLastError());
//
//	std::cout << std::endl;
//	std::system("pause");
//	isConnected = false;
//}
//
//pingTimer.Restart();
////start communication
//while (isConnected == true)
//{
//	//std::cout << "Enter message : " << messageToSend.Message << std::endl;
//	/*std::string messageString = "apa";
//	message[0] = messageString.c_str();*/
//	char * message = reinterpret_cast<char*>(&messageToSend);
//
//
//	//send the message
//
//
//	//receive a reply and print it
//	//clear the buffer by filling null, it might have previously received data
//	memset(buf, '\0', BUFLEN);
//	//try to receive some data, this is a blocking call
//	int RecieveResult;
//	if (RecieveResult = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
//	{
//		const int SocketError = WSAGetLastError();
//
//		if (SocketError != 10035)
//		{
//			printf("recvfrom() failed with error code : %d", WSAGetLastError());
//		}
//		//exit(EXIT_FAILURE);
//	}
//	else
//	{
//		NetworkMessage & recievedMessage = *reinterpret_cast<NetworkMessage*>(buf);
//
//		if (recievedMessage.Type == MessageType::eMessage)
//		{
//			puts(recievedMessage.Message);
//		}
//		else if (recievedMessage.Type == MessageType::eConnect)
//		{
//			std::cout << "connection confirmed from server" << std::endl;
//		}
//		else if (recievedMessage.Type == MessageType::ePing)
//		{
//			NetworkMessage pingMessage;
//			pingMessage.Type = MessageType::ePing;
//			memcpy(pingMessage.Message, ClientName.c_str(), ClientName.length() + 1);
//
//			char * message = reinterpret_cast<char*>(&pingMessage);
//
//			if (sendto(s, message, sizeof(messageToSend), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
//			{
//				printf("sendto() failed with error code : %d", WSAGetLastError());
//				//exit(EXIT_FAILURE);
//			}
//
//			std::cout << connectionMessage.Message << " recieved ping from server" << " Ping count " << pingCounter++ << std::endl;
//			pingTimer.Restart();
//		}
//	}
//
//	if (pingTimer.GetElapsedTime().InSeconds() >= 10.f)
//	{
//		isConnected = false;
//
//		std::cout << "lost Connection to server" << std::endl;
//	}
//}
//
