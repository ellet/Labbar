#include "stdafx.h"

#include<stdio.h>
#include<Winsock2.h>
#include <thread>
#include <iostream>
#include "Client.h"


 //Winsock Library
#pragma comment(lib, "Ws2_32.lib")




int main()
{
	Client client;

	client.Startup();

	while (client.IsRunning() == true)
	{
		client.Update();
	}

	client.Shutdown();

	return 0;
}

