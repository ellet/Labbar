#pragma once
//#include "stdafx.h"
#include <string>
#include <fstream>
#include <cassert>

#pragma region Debug Macros
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	_CRTIMP void __cdecl _wassert(_In_z_ const wchar_t * _Message, _In_z_ const wchar_t *_File, _In_ unsigned _Line);

#ifdef __cplusplus
}

#endif  /* __cplusplus */

#define DL_ASSERT(statement, string)  if ((statement) == false) { (DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__, __LINE__, __FUNCTION__, (string))); }

#define DL_PRINT(string)  DL_Debug::Debug::GetInstance()->PrintMessage(string);

#define DL_PRINTCRASHMESSAGE(string) DL_Debug::Debug::GetInstance()->CrashMessage(string);

#define DL_WRITELOG(log,...) DL_Debug::Debug::GetInstance()->WriteLog(log, __VA_ARGS__);

#define  USE_FILTERLOG

#ifdef USE_FILTERLOG
#define RESOURCE_LOG(...) DL_WRITELOG("Resource", __VA_ARGS__);
#define ENGINE_LOG(...) DL_WRITELOG("Engine", __VA_ARGS__);
#define INPUT_LOG(...) DL_WRITELOG("Input", __VA_ARGS__);
#else
#define RESOURCE_LOG(...);
#define ENGINE_LOG(...);
#define INPUT_LOG(...);
#endif

#define DL_DEBUG( ... )  DL_Debug::Debug::GetInstance()->DebugMessage(__LINE__,__FILE__,__VA_ARGS__);
#pragma endregion


namespace DL_Debug
{
	class Debug
	{
	public:
		static bool Create(const std::string& aFile = "Debug_Logs");
		static void Destroy();
		static Debug* GetInstance();
		
		void AssertMessage(const char * aFileName, int aLine, const char * aFunctionName, const char * aString);
		void PrintMessage(const char * aString);
		void DebugMessage(const int aLine, const char * aFileName, const char * aFormattedString, ...);
		void WriteLog(const std::string & aLogIdentifier, const char * aFormattedString, ...);
		
		void StartCrashMessage();
		void CrashMessage(const char * aString);
		void EndCrashMessage();

		void ActivateFilterlog(const std::string & aFilter);

	private:
		Debug();
		~Debug();

		bool ValidateLogFilterName(const std::string & aFilterName);
		std::string GetHourMinSecAsString();
		std::string GetCurrentTimeAsString();

		std::string myLogsFolderLocation;
		static Debug* ourInstance;

		std::unordered_map<std::string, std::ofstream> myLogsOutput;

		/*std::ofstream myOutput;
		std::ofstream myCrashOutput;*/
		std::string myCrashOutputLocation;
	};
}



