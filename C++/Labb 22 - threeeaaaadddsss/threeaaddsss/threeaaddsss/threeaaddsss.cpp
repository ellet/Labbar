// threeaaddsss.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <Winuser.h>
#include <vector>
#include <thread>
#include <atomic>
#include "ThreadPrimes.h"




int _tmain(int argc, _TCHAR* argv[])
{
	ThreadPrimes counter(3);


	while (GetKeyState(VK_RETURN) == 0)
	{
		Sleep(1);
	}

	counter.EndCount();

	counter.CheckAllThreadsEnded();

	system("pause");

	return 0;
}