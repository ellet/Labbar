#include "stdafx.h"


#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512  //Max length of buffer
#define PORT 23073   //The port on which to listen for incoming data

int main()
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	unsigned short pingCounter = 0;

	slen = sizeof(si_other);

	bool hasConnection = false;

	SB::Stopwatch connectionTimer;
	SB::Stopwatch pingTimer;

	std::string ConnectedName = "No Connection";

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	u_long blocking = 1;
	ioctlsocket(s, FIONBIO, &blocking);

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	//keep listening for data
	while (1)
	{
		//std::cout << "Waiting for data..." << std::endl;
		//fflush(stdout);

		

		if (hasConnection == true)
		{
			if (connectionTimer.GetElapsedTime().InSeconds() > 10.f)
			{
				hasConnection = false;
				std::cout << ConnectedName << " has timed out" << std::endl;
			}
			else if (pingTimer.GetElapsedTime().InSeconds() >= 1.f)
			{
				pingTimer.Restart();
				NetworkMessage pingMessage;
				pingMessage.Type = MessageType::ePing;
				memcpy(pingMessage.Message, "Server", 7);

				char * message = reinterpret_cast<char*>(&pingMessage);

				if (sendto(s, message, sizeof(pingMessage), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
				{
					std::cout << "sendto() failed with error code : %d" << WSAGetLastError() << std::endl;
					//exit(EXIT_FAILURE);
				}
			}

			
		}


		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);

		if (recv_len == SOCKET_ERROR)
		{
			const int SocketError = WSAGetLastError();

			if (SocketError == 10054)
			{
				std::cout << "Lost Connection to: " << ConnectedName << std::endl;
				hasConnection = false;
				ConnectedName = "";
			}
			else if (SocketError != 10035)
			{
				std::cout << "recvfrom() failed with error code : %d" << SocketError << std::endl;
				//exit(EXIT_FAILURE);
			}

			//print details of the client/peer and the data received
		}
		else
		{
			//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
			NetworkMessage & recievedMessage = *reinterpret_cast<NetworkMessage*>(buf);

			if (recievedMessage.Type == MessageType::eMessage)
			{
				std::cout << recievedMessage.Message << std::endl;
			}
			else if (recievedMessage.Type == MessageType::eConnect)
			{
				hasConnection = true;
				ConnectedName = recievedMessage.Message;

				std::cout << recievedMessage.Message << " has connected" << std::endl;

				NetworkMessage ConnectionAcceptedMessage;
				ConnectionAcceptedMessage.Type = MessageType::eConnect;
				memcpy(ConnectionAcceptedMessage.Message, "Server", 7);

				char * message = reinterpret_cast<char*>(&ConnectionAcceptedMessage);

				if (sendto(s, message, sizeof(ConnectionAcceptedMessage), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
				{
					std::cout << "sendto() failed with error code : %d" << WSAGetLastError() << std::endl;
					//exit(EXIT_FAILURE);
				}

				connectionTimer.Restart();
				pingTimer.Restart();
			}
			else if (recievedMessage.Type == MessageType::ePing)
			{
				std::cout << "Server recieved ping from " << recievedMessage.Message << " ping count: " << pingCounter++ << std::endl;
				connectionTimer.Restart();
				pingTimer.Restart();
			}

			//printf("Data: %s\n", buf);

			//now reply the client with the same data
			
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}
