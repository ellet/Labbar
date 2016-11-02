// KrashyKrashy.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include "stdafx.h"
#include <wtypes.h>
#include <iostream>
#include <Dbghelp.h>


//#pragma comment(lib, "Dbghelp")

std::wstring gloablPrettyOutput;

void RunGame()
{
	*((int*)0) = 0;

	int a = 0; int b = 5 / a;
}

HANDLE CreateAwesomeFile()
{
	HANDLE hFile;
	//char DataBuffer[] = "This is some test data to write to the file.";
	//DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	//DWORD dwBytesWritten = 0;
	//BOOL bErrorFlag = FALSE;

	
	char name[MAX_PATH];
	{
		auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
		SYSTEMTIME t;
		GetSystemTime(&t);
		wsprintfA(nameEnd - strlen(".exe"),
			"_%4d%02d%02d_%02d%02d%02d.dmp",
			t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	}

	std::string tempString(name);
	std::wstring tempWstring(tempString.begin(), tempString.end());

	hFile = CreateFile(tempWstring.c_str(),                // name of the write
		GENERIC_WRITE,          // open for writing
		FILE_SHARE_READ,                      // do not share
		NULL,                   // default security
		CREATE_ALWAYS,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	

	return hFile;
}

void CreateMiniDump(_EXCEPTION_POINTERS* anExceptionPoiter)
{
	auto hDbgHelp = LoadLibraryA("dbghelp");
	if (hDbgHelp == nullptr)
		return;
	auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
	if (pMiniDumpWriteDump == nullptr)
		return;


	HWND tempHwnd = GetActiveWindow();
	/*DWOR tempProcessID = new DWORD;
	GetWindowThreadProcessId(tempHwnd, tempProcessID);*/

	HANDLE tempHProcess = GetCurrentProcess();

	MINIDUMP_TYPE tempDumpType = MINIDUMP_TYPE::MiniDumpNormal;

	MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
	exceptionInfo.ThreadId = GetCurrentThreadId();
	exceptionInfo.ExceptionPointers = anExceptionPoiter;
	exceptionInfo.ClientPointers = FALSE;

	char name[MAX_PATH];
	{
		auto nameEnd = name;//+ GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
		SYSTEMTIME t;
		GetSystemTime(&t);
		wsprintfA(nameEnd,//-strlen(".exe"),
			"MiniDump_%4d%02d%02d_%02d%02d%02d.dmp",
			t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	}

	std::string tempString(name);
	std::wstring tempWstring(tempString.begin(), tempString.end());

	gloablPrettyOutput = tempWstring;

	HANDLE tempCrashFile = CreateFile(tempWstring.c_str(),                // name of the write
		GENERIC_WRITE,          // open for writing
		FILE_SHARE_READ,                      // do not share
		NULL,                   // default security
		CREATE_ALWAYS,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);

	if (tempCrashFile == INVALID_HANDLE_VALUE)
	{
		int apa = 10;
		apa++;
	}

	bool test = pMiniDumpWriteDump(tempHProcess, GetCurrentProcessId(), tempCrashFile, MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory), anExceptionPoiter ? &exceptionInfo : nullptr, NULL, NULL);

	if (test == false)
	{
		HRESULT error = S_OK;

		error = (HRESULT)GetLastError();

		int apa = 10;
		apa++;

		
	}

	CloseHandle(tempCrashFile);


}

LONG WINAPI GetTheKrashy(_EXCEPTION_POINTERS* anExceptionPoiter)
{
	
	CreateMiniDump(anExceptionPoiter);

	std::wstring outPut;

	outPut = L"A minidump was created at bin/" + gloablPrettyOutput + L" , please tell a programmer.";

	MessageBox(NULL, outPut.c_str(), L"KRASSSIIIIHHHUUIII", MB_OK);

	return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
	__try
	{
		RunGame();
	}
	__except (GetTheKrashy(GetExceptionInformation()))
	{
	
	}

    return 0;
}

