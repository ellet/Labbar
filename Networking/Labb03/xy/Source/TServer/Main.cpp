#include "stdafx.h"
#include "ServerMain.h"




int main()
{
	CServerMain server;

	server.StartServer();

	while (server.IsRunning() == true)
	{
		server.Update();
	};


}

