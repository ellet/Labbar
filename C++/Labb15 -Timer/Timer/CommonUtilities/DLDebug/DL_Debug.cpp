//#include "stdafx.h"
#include "DL_Debug.h"
#include "DL_StackWalker.h"
#include <sstream>
#include <cstdarg>
#include <cassert>
#include <time.h>
#include <Windows.h>
using namespace DL_Debug;

Debug *Debug::ourInstance;

//-----------------------------------------------------------------

Debug::Debug()
{
	ourInstance = nullptr;
}

Debug::~Debug()
{
	ourInstance->myOutput.close();

	delete ourInstance;
	ourInstance = nullptr;
}

//-----------------------------------------------------------------

bool Debug::Create(const std::string& aFile)
{
	assert(ourInstance == nullptr && "DEBUG TOOL ERROR  -  ourInstance is not nullptr");
	ourInstance = new Debug();
	if (ourInstance == nullptr)
	{
		return false;
	}

	const LPCTSTR DebugLogsFolder = aFile.c_str();
	CreateDirectory(DebugLogsFolder, NULL);

	std::stringstream tempStream;
	tempStream << aFile.c_str() << "/" << std::endl;
	std::string tester(aFile.begin(), aFile.end());

	std::string temp = ourInstance->GetCurrentTimeAsString() + ".txt";
	temp = tester + "/" + temp;

	ourInstance->myOutput = std::ofstream(temp, std::ofstream::out);
	return true;
}

void Debug::Destroy()
{
	ourInstance->myOutput.close();

	delete ourInstance;
	ourInstance = nullptr;

}

Debug* Debug::GetInstance()
{
	return (ourInstance);
}

//-----------------------------------------------------------------

void Debug::AssertMessage(const char* aFileName, int aLine, const char* aFunctionName, const char* aString)
{
	std::ostringstream temp;
	temp << "Program crashed in file: " << aFileName << std::endl;
	temp << "At line: " << aLine << std::endl;
	temp << "In function: " << aFunctionName << std::endl;
	temp << aString << std::endl;

	std::string errorMessage = temp.str();
	DL_PRINT(errorMessage.c_str());
	
	std::wostringstream tempstream;

	tempstream << errorMessage.c_str();
	const std::wstring Message = tempstream.str().c_str();

	tempstream << aFileName;
	const std::wstring File = tempstream.str().c_str();
	DL_Debug::StackWalker tempStackWalker;

	DL_PRINT("\nStack Crash Log Below:");
	tempStackWalker.ShowCallstack();

	_wassert(Message.c_str(), File.c_str(), aLine);
	//_wassert(_CRT_WIDE("a message"), _CRT_WIDE(__FILE__), __LINE__)
}

void Debug::PrintMessage(const char * aString)
{
	ourInstance->myOutput << aString << std::endl;
	ourInstance->myOutput << "---------------" << std::endl;
}

void Debug::DebugMessage(const int aLine, const char * aFileName, const char * aFormattedString, ...)
{
	
	std::ostringstream temp;
	temp << "Debug message from file: " << aFileName << std::endl;
	temp << "At line: " << aLine << std::endl;
	// ---- magic
	char buffer[1024];
	va_list args;
	va_start(args, aFormattedString);
	vsprintf_s(buffer, aFormattedString, args);
	perror(buffer);
	va_end(args);
	//------
	temp << buffer << std::endl;
	DL_PRINT(temp.str().c_str());
}

//-----------------------------------------------------------------

std::string Debug::GetCurrentTimeAsString()
{
	struct tm newtime;
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.

	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}

	// Convert to an ASCII representation. 
	err = asctime_s(timebuf, 26, &newtime);
	if (err)
	{
		printf("Invalid argument to asctime_s.");
		exit(1);
	}

	std::string removeColons = timebuf;

	removeColons.resize(removeColons.size() - 1);

	for (size_t iChar = 0; iChar < removeColons.size(); ++iChar)
	{
		if (removeColons[iChar] == ':')
		{
			removeColons[iChar] = '-';
		}
	}

	return removeColons;
}