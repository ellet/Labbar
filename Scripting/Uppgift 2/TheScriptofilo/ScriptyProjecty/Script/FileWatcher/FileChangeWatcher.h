#pragma once
//#include <windows.h>
//#include <unordered_map>
//#include "Time\Stopwatch.h"


//enum class FileChangeWatcherNotificationFormat
//{
//	eForwardSlashes,
//	eBackSlashes,
//	eDefault
//};
//
//class FileChangeWatcher
//{
//public:
//	// Pass nullptr or an empty string to myWatch working directory
//	FileChangeWatcher();
//	~FileChangeWatcher();
//
//	void Init(const wchar_t * aDirectory = nullptr, FileChangeWatcherNotificationFormat aFormat = FileChangeWatcherNotificationFormat::eForwardSlashes);
//
//	void CheckChanges();
//
//private:
//	//void ThreadFunction(std::wstring aDirectoryToWatch, std::atomic<bool> *stopThreadFlag);
//
//		
//	FileChangeWatcherNotificationFormat myFormat;
//		
//	std::unordered_map<std::string, float> lastTime;
//	std::wstring myDirectoryToWatch;
//
//	void * myDirectoryHandle;
//
//	struct ChangeEntry
//	{
//		float postTime;
//		std::string file;
//	};
//
//	std::vector<ChangeEntry> myChanges;
//	Stopwatch myStopWatch;
//};
