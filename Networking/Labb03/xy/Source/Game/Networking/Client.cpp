#include "stdafx.h"
#include "Client.h"
#include "Messages\ConnectNetMessage.h"
#include "Messages\PingNetMessage.h"
#include "Messages\ChatNetMessage.h"
#include "Messages\DisconnectNetMessage.h"
#include "..\GameWorld.h"
#include "Messages\SyncGameObjectMessage.h"
#include "Messages\CreateGameObjectMessage.h"
#include "Messages\CreateDummyNetMessage.h"
#include "Messages\GameStateNetMessage.h"
#include "Messages\ScoreNetMessage.h"
#include "Messages\ImportantNetMessage.h"

#pragma comment(lib,"ws2_32.lib")

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 23073   //The port on which to listen for incoming data

Client::Client()
{
	myIsConnected = false;

	myServerDataLength = sizeof(myServerData);

	myShouldShutDown = false;

	myMessageCounter = 0;
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

	
	myMessageManager.SetUserID(0);
	myMessageManager.SetTargetID(globalServerID);
	
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
	UpdateImportantMessages();

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
#ifndef _DEBUG
			PrintClientMessage("trying to reconnect to server...");
			ConnectToServer();
#endif
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
	if (aMessageToSend.GetMessageType() > NetworkMessageTypes::eIMPORTANTCUTTOF)
	{
		Error("message is not sent as important");
	}

	SendNetMessage(aMessageToSend);
}


void Client::SendMesseageFromWorld(ImportantNetMessage & aMessageToSend)
{
	SendNetMessage(aMessageToSend);
}

void Client::SendNetMessage(NetMessage & aMessageToSend)
{
	aMessageToSend.PackMessage();

	SendNetMessage(aMessageToSend.myStream);
}

void Client::SendNetMessage(StreamType & message)
{
	if (sendto(mySocket, &message[0], message.size(), 0, (struct sockaddr *) &myServerData, myServerDataLength) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("sendto() failed with error code : " + std::to_string(WSAGetLastError()));
	}
}

bool Client::HandleImportantMessage(ImportantNetMessage & aImportantMessage)
{
	if (aImportantMessage.GetMessageType() == NetworkMessageTypes::eGameStateMessage)
	{
		int apa = 10;
		++apa;
	}

	

	if (aImportantMessage.GetSenderID() != globalServerID)
	{
		bool messageFound = false;

		std::unordered_map<unsigned short, ImportantMessageData>::iterator messageCheck = myImportantMessages.find(static_cast<unsigned short>(aImportantMessage.myImpID));
		if (messageCheck != myImportantMessages.end())
		{
			myImportantMessages.erase(messageCheck);	

			messageFound = true;
		}

		if (messageFound == true)
		{
			IMPORTANTMESSAGEPRINT("Message with ID: " + std::to_string(aImportantMessage.myImpID) + "was found and deleted");
		}

		return false;
	}
	else
	{
		IMPORTANTMESSAGEPRINT("Sending back message with ID: " + std::to_string(aImportantMessage.myImpID));

		SendNetMessage(aImportantMessage);
		std::unordered_map<unsigned short, SB::Stopwatch>::iterator recievedCheck = myRecievedMessages.find(static_cast<unsigned short>( aImportantMessage.myImpID));

		if (recievedCheck == myRecievedMessages.end())
		{
			

			myRecievedMessages[static_cast<unsigned short> (aImportantMessage.myImpID)];
			return true;
		}
		else
		{
			IMPORTANTMESSAGEPRINT("Message with ID: " + std::to_string(aImportantMessage.myImpID) + " has already been handled");

			return false;
		}
	}
}

void Client::UpdateImportantMessages()
{
	if (myImportantMessages.size() > 0)
	{
		int apa = 10;
		++apa;
	}

	std::unordered_map<unsigned short, ImportantMessageData>::iterator messageCheck = myImportantMessages.begin();
	for (; messageCheck != myImportantMessages.end(); ++messageCheck)
	{
		if (messageCheck->second.timerOutTimer.GetElapsedTime().InSeconds() > globalImportantMessageTimeout)
		{
			ImportantNetMessage derp;
			derp.UnPackMessage(&messageCheck->second.myStream[0], messageCheck->second.myStream.size());

			if (derp.GetMessageType() == NetworkMessageTypes::eConnection)
			{
				ConnectNetMessage arar;
				arar.UnPackMessage(&messageCheck->second.myStream[0], messageCheck->second.myStream.size());
				int apa = 10;
				++apa;
			}

			IMPORTANTMESSAGEPRINT("Resending with ID" + std::to_string(messageCheck->first));
			SendNetMessage(messageCheck->second.myStream);
			messageCheck->second.timerOutTimer.Restart();
		}
	}

	std::unordered_map<unsigned short, SB::Stopwatch>::iterator timer = myRecievedMessages.begin();
	std::unordered_map<unsigned short, SB::Stopwatch>::iterator removeIterator = myRecievedMessages.end();
	for (; timer != myRecievedMessages.end(); ++timer)
	{
		if (removeIterator != myRecievedMessages.end())
		{
			myRecievedMessages.erase(removeIterator);
			removeIterator = myRecievedMessages.end();
		}

		if (timer->second.GetElapsedTime().InSeconds() > globalImportantPacketKeepTimeout)
		{
			removeIterator = timer;
		}
	}

	if (removeIterator != myRecievedMessages.end())
	{
		myRecievedMessages.erase(removeIterator);
		removeIterator = myRecievedMessages.end();
	}
}

unsigned short Client::GetNewImportantMessageID()
{
	unsigned short newID = myMessageCounter++;

	if (myMessageCounter > 35000)
	{
		myMessageCounter = 0;
	}

	return newID;
}

void Client::RecieveMessages()
{

	char buf[BUFLEN];
	int recieveLengthOfMessage = 0;
	

	memset(buf, '\0', BUFLEN);

	
	do
	{
		recieveLengthOfMessage = recvfrom(mySocket, buf, BUFLEN, 0, (struct sockaddr *) &myServerData, &myServerDataLength);
		unsigned short lenghOfMessage = static_cast<unsigned short>(recieveLengthOfMessage);
	

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

			bool readMessage = true;
			if (NetMessage::isImportant(messageType) == true)
			{
				ImportantNetMessage impMessage;
				impMessage.UnPackMessage(buf, lenghOfMessage);

				if (impMessage.GetSenderID() > 25 && impMessage.GetSenderID() != 1337)
				{
					int apa = 10;
					++apa;
				}

				readMessage = HandleImportantMessage(impMessage);
			}

			if (readMessage)
			{
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

				case NetworkMessageTypes::eDummyCreate:
				{
					CreateDummyNetMessage recievedMessage;
					recievedMessage.UnPackMessage(buf, lenghOfMessage);

					myGameWorld->RecieveMessage(recievedMessage);
				}
				break;

				case NetworkMessageTypes::eGameStateMessage:
				{
					GameStateNetMessage recievedMessage;
					recievedMessage.UnPackMessage(buf, lenghOfMessage);

					myGameWorld->RecieveMessage(recievedMessage);
				}
				break;

				case NetworkMessageTypes::eScore:
				{
					ScoreNetMessage recievedMessage;
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

	} while (recieveLengthOfMessage > 0);
}

void Client::SendNetMessage(ImportantNetMessage & aMessage)
{
	if (aMessage.GetSenderID() == myMessageManager.GetUserID())
	{
		ImportantMessageData data;

		data.messageID = GetNewImportantMessageID();
		aMessage.myImpID = data.messageID;
		aMessage.PackMessage();

		data.myStream = aMessage.myStream;
		data.targetID = aMessage.GetTargetID();

		SendNetMessage(aMessage.myStream);

		if (myImportantMessages.find(data.messageID) != myImportantMessages.end())
		{
			Error("duplicate important message id");
		}

	
		myImportantMessages[data.messageID] = data;
		myImportantMessages[data.messageID].timerOutTimer.Restart();
	}
	else
	{
		aMessage.PackMessage();
		SendNetMessage(aMessage.myStream);
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
	SendNetMessage(discMessage);

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
	//connectMessage.PackMessage();
	

	myIsConnected = false;

	SendNetMessage(connectMessage);
	/*if (sendto(mySocket, &connectMessage.myStream[0], connectMessage.myStream.size(), 0, (struct sockaddr *) &myServerData, myServerDataLength) == SOCKET_ERROR)
	{
		SomethingWentWrongMessage("sendto() failed with error code : " + std::to_string(WSAGetLastError()));
	}*/

	
	
	myConnectionTimer.Restart();
}

