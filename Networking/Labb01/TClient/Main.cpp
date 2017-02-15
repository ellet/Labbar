#include "stdafx.h"

#include<stdio.h>
#include<Winsock2.h>
#include <thread>
#include <iostream>


 //Winsock Library
#pragma comment(lib, "Ws2_32.lib")

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 23073   //The port on which to listen for incoming data



int main()
{
	bool isConnected = true;
	SB::Stopwatch pingTimer;

	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	//char message[BUFLEN];
	//char * message = "apa";

	std::string ServerIPString;
	std::string ClientName;

	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}

	u_long blocking = 1;
	ioctlsocket(s, FIONBIO, &blocking);

	std::cout << "Input Server IP: ";
	std::getline(std::cin, ServerIPString);
	std::cout << std::endl;

	if (ServerIPString == "")
	{
		ServerIPString = SERVER;
	}

	std::cout << "Input Client Name: ";
	std::getline(std::cin, ClientName);
	std::cout << std::endl;

	if (ClientName == "")
	{
		ClientName = "Bertil";
	}



	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	//si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	si_other.sin_addr.S_un.S_addr = inet_addr(ServerIPString.c_str());

	NetworkMessage messageToSend;
	messageToSend.Type = MessageType::eMessage;
	memcpy(messageToSend.Message, "apa", 4);

	std::cout << "Input Server IP" << std::endl;

	
	std::cout << "ServerIp is: " << ServerIPString << std::endl;
	std::cout << "Client Name is: " << ClientName << std::endl;

	NetworkMessage connectionMessage;
	connectionMessage.Type = MessageType::eConnect;
	memcpy(connectionMessage.Message, ClientName.c_str(), ClientName.length() + 1);

	unsigned short pingCounter = 0;

	char * message = reinterpret_cast<char*>(&connectionMessage);

	if (sendto(s, message, sizeof(messageToSend), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		
		std::cout << std::endl;
		std::system("pause");
		isConnected = false;
	}

	pingTimer.Restart();
	//start communication
	while (isConnected == true)
	{
		//std::cout << "Enter message : " << messageToSend.Message << std::endl;
		/*std::string messageString = "apa";
		message[0] = messageString.c_str();*/
		char * message = reinterpret_cast<char*>(&messageToSend);
		

		//send the message
		

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		int RecieveResult;
		if (RecieveResult = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			const int SocketError = WSAGetLastError();

			if (SocketError != 10035)
			{
				printf("recvfrom() failed with error code : %d", WSAGetLastError());
			}
			//exit(EXIT_FAILURE);
		}
		else
		{
			NetworkMessage & recievedMessage = *reinterpret_cast<NetworkMessage*>(buf);

			if (recievedMessage.Type == MessageType::eMessage)
			{
				puts(recievedMessage.Message);
			}
			else if (recievedMessage.Type == MessageType::eConnect)
			{
				std::cout << "connection confirmed from server" << std::endl;
			}
			else if (recievedMessage.Type == MessageType::ePing)
			{
				NetworkMessage pingMessage;
				pingMessage.Type = MessageType::ePing;
				memcpy(pingMessage.Message, ClientName.c_str(), ClientName.length() + 1);

				char * message = reinterpret_cast<char*>(&pingMessage);

				if (sendto(s, message, sizeof(messageToSend), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
				{
					printf("sendto() failed with error code : %d", WSAGetLastError());
					//exit(EXIT_FAILURE);
				}

				std::cout << connectionMessage.Message << " recieved ping from server" << " Ping count " << pingCounter++ << std::endl;
				pingTimer.Restart();
			}
		}

		if (pingTimer.GetElapsedTime().InSeconds() >= 10.f)
		{
			isConnected = false;

			std::cout << "lost Connection to server" << std::endl;
		}
	}

	std::cout << "Shutting down client" << std::endl;
	std::system("pause");

	closesocket(s);
	WSACleanup();

	return 0;
}
