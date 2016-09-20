#include "stdafx.h"
#include "DL_Debug.h"
#include "DL_StackWalker.h"
#include <sstream>
#include <cstdarg>
#include <cassert>
#include <time.h>
#include <Windows.h>
#include "CU/Utility/WindowsFunctions/WindowsFunctions.h"
#include "CU/NameSpaceAliases.h"

using namespace DL_Debug;

Debug *Debug::ourInstance = nullptr;

//-----------------------------------------------------------------

Debug::Debug()
{
	ourInstance = nullptr;
}

Debug::~Debug()
{
	for (std::unordered_map<std::string, std::ofstream>::iterator iLogs = myLogsOutput.begin(); iLogs != myLogsOutput.end(); iLogs++)
	{
		iLogs->second.close();
	}
}

//-----------------------------------------------------------------

bool Debug::Create(const std::string& aFile)
{
	(aFile);
	assert(ourInstance == nullptr && "DEBUG TOOL ERROR  -  ourInstance is not nullptr");
	ourInstance = new Debug();
	if (ourInstance == nullptr)
	{
		return false;
	}	

	CU::WindowsFunctions::CreateFolder(aFile);
	windowsString CrashLogsFolder = CU::WindowsFunctions::CreateFolder(aFile, "Logs");

	ourInstance->myLogsFolderLocation = std::string(CrashLogsFolder.begin(), CrashLogsFolder.end());

	std::string tempTimeStampString = "/" + ourInstance->GetCurrentTimeAsString() + ".txt";


	windowsString tempTimeCorrectFormat(tempTimeStampString.begin(), tempTimeStampString.end());

	//ourInstance->myOutput = std::ofstream(aFile + tempTimeCorrectFormat, std::ofstream::out);
	//ourInstance->myCrashOutputLocation = CrashLogsFolder + tempTimeCorrectFormat;

	return true;
}

void Debug::Destroy()
{
	if (ourInstance != nullptr)
	{
		//ourInstance->myOutput.close();
	}
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
	StartCrashMessage();
	std::ostringstream temp;
	temp << "Program crashed in file: " << aFileName << std::endl;
	temp << "At line: " << aLine << std::endl;
	temp << "In function: " << aFunctionName << std::endl;
	temp << aString << std::endl;

	std::string errorMessage = temp.str();
	DL_PRINTCRASHMESSAGE(errorMessage.c_str());
	
	std::wostringstream tempstream;

	tempstream << errorMessage.c_str();
	const std::wstring Message = tempstream.str().c_str();

	tempstream << aFileName;
	const std::wstring File = tempstream.str().c_str();
	DL_Debug::StackWalker tempStackWalker;

	DL_PRINTCRASHMESSAGE("\nStack Crash Log Below:");
	tempStackWalker.ShowCallstack();

	EndCrashMessage();

	_wassert(Message.c_str(), File.c_str(), aLine);
	//_wassert(_CRT_WIDE("a message"), _CRT_WIDE(__FILE__), __LINE__)
}

void Debug::PrintMessage(const char * aString)
{
	std::cout << aString << std::endl;
	//ourInstance->myOutput << aString << std::endl;
	//ourInstance->myOutput << "---------------" << std::endl;
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

void DL_Debug::Debug::WriteLog(const std::string & aLogIdentifier, const char * aFormattedString, ...)
{
	if (myLogsOutput[aLogIdentifier].is_open() == true)
	{
		char buffer[1024];
		va_list args;
		va_start(args, aFormattedString);
		vsprintf_s(buffer, aFormattedString, args);
		//perror(buffer);
		va_end(args);

		std::string TempString(GetHourMinSecAsString());

		TempString += " ";
		TempString += buffer;

		myLogsOutput[aLogIdentifier] << TempString << std::endl;
	}
}

void DL_Debug::Debug::StartCrashMessage()
{
	//ourInstance->myCrashOutput = std::ofstream(myCrashOutputLocation, std::ofstream::out);
}

void DL_Debug::Debug::CrashMessage(const char * aString)
{
	(aString);
	//ourInstance->myCrashOutput << aString << std::endl;
	//ourInstance->myCrashOutput << "---------------" << std::endl;
}

void DL_Debug::Debug::EndCrashMessage()
{
	//ourInstance->myCrashOutput.close();
}

void DL_Debug::Debug::ActivateFilterlog(const std::string & aFilter)
{
	if (ValidateLogFilterName(aFilter) == true)
	{
		ourInstance->myLogsOutput[aFilter] = std::ofstream(myLogsFolderLocation + "/" + aFilter + ".txt", std::ofstream::out);
	}
}

bool DL_Debug::Debug::ValidateLogFilterName(const std::string & aFilterName)
{
	if (aFilterName == "Resource")
	{
		return true;
	}
	else if (aFilterName == "Engine")
	{
		return true;
	}
	else if (aFilterName == "Input")
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string DL_Debug::Debug::GetHourMinSecAsString()
{
	time_t tempTicks = time(0);   // get time now
	tm tempCurrentTime;;

	std::stringstream myTimeConverter;

	localtime_s(&tempCurrentTime, &tempTicks);

	myTimeConverter << "[" << tempCurrentTime.tm_hour << ":" << tempCurrentTime.tm_min << ":" << tempCurrentTime.tm_sec << "]";

	return myTimeConverter.str();
}