//#include "stdafx.h"
//#include "FileChangeWatcher.h"
//#include <processenv.h>
//#include <iostream>
//#include <fileapi.h>
//#include <winbase.h>



//FileChangeWatcher::FileChangeWatcher()
//{
//
//	/*myStopThread = new std::atomic<bool>();
//	myStopThread->store(false);
//	myThread = new std::thread(std::bind(&FileChangeWatcher::ThreadFunction, this, directoryToWatch, myStopThread));*/
//}
//
//FileChangeWatcher::~FileChangeWatcher()
//{
//	//myStopThread->store(true);
//
//	/* =(
//
//	if (myThread != nullptr)
//	{
//		myThread->join();
//		delete myThread;
//		myThread = nullptr;
//	}*/
//}
//
//
//
//void FileChangeWatcher::Init(const wchar_t * aDirectory /*= nullptr*/, FileChangeWatcherNotificationFormat aFormat /*= FileChangeWatcherNotificationFormat::eForwardSlashes*/)
//{
//	myFormat = aFormat;
//
//	myDirectoryToWatch = aDirectory;
//
//	if (aDirectory == nullptr || wcslen(aDirectory) == 0)
//	{
//		wchar_t buffer[MAX_PATH];
//		if (GetCurrentDirectoryW(MAX_PATH, buffer) == 0)
//		{
//			std::cout << "FileChangeWatcher failed to find the working directory. You will not be notified of changes." << std::endl;
//			return;
//		}
//		myDirectoryToWatch= buffer;
//	}
//	else
//	{
//		myDirectoryToWatch = aDirectory;
//	}
//
//#ifdef UNICODE
//	std::wstring folderInput(myDirectoryToWatch.begin(), myDirectoryToWatch.end());
//#else
//	std::string folderInput(myDirectoryToWatch.begin(), myDirectoryToWatch.end());
//#endif
//
//	myDirectoryHandle = CreateFile(folderInput.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr,
//		OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
//
//	if (myDirectoryHandle == INVALID_HANDLE_VALUE)
//	{
//		std::cout << " directory handle was invlid " << std::endl;
//		abort();
//		return;
//	}
//}
//
//void FileChangeWatcher::CheckChanges()
//{
//	FILE_NOTIFY_INFORMATION notifications[255];
//
//	FILE_NOTIFY_INFORMATION * current = notifications;
//	DWORD bytesReturned;
//
//	if (ReadDirectoryChangesW(myDirectoryHandle, notifications, sizeof(notifications), true, FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, nullptr, nullptr))
//	{
//		/*if (stopThreadFlag->load() == true)
//		{
//			return;
//		}*/
//
//		for (;;)
//		{
//			std::vector<wchar_t> data;
//			data.resize(current->FileNameLength + sizeof(wchar_t));
//			memcpy(&data[0], current->FileName, current->FileNameLength);
//			data[data.size() - sizeof(wchar_t)] = L'\0';
//
//			std::string fileName;
//
//			if (myFormat == FileChangeWatcherNotificationFormat::eDefault)
//			{
//				fileName = std::string(data.begin(), data.end());
//			}
//			else
//			{
//				fileName.resize((data.size() / sizeof(wchar_t)) - 1);
//
//				for (size_t i = 0; i < fileName.size(); i++)
//				{
//					if (data[i] == L'\\')
//					{
//						if (myFormat == FileChangeWatcherNotificationFormat::eForwardSlashes)
//						{
//							fileName[i] = '/';
//							continue;;
//						}
//					}
//					else if (data[i] == '/')
//					{
//						if (myFormat == FileChangeWatcherNotificationFormat::eBackSlashes)
//						{
//							fileName[i] = '\\';
//							continue;
//						}
//					}
//
//					fileName[i] = static_cast<char>(data[i]);
//				}
//			}
//
//			auto currentTime = myStopWatch.GetElapsedTime().InSeconds();
//			auto &&lastTimeIt = lastTime.find(fileName);
//
//			if (lastTime.find(fileName) == lastTime.end()) /*||
//				currentTime > lastTimeIt->second + myMinimumTimeDifference)*/
//			{
//				myChanges.push_back(ChangeEntry
//				{
//					currentTime + 0.2f,
//					fileName
//				});
//
//				lastTime[fileName] = currentTime;
//			}
//
//			if (current->NextEntryOffset == 0)
//			{
//				break;
//			}
//
//			current = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<char*>(current) + current->NextEntryOffset);
//		}
//	}
//}
//		/*else
//		{
//			Sleep(250);
//		}*/
//
///*DWORD waitStatus = WaitForSingleObject(waitHandle, 250);
//
//switch (waitStatus)
//{
//case WAIT_OBJECT_0:
//if (FindNextChangeNotification(waitHandle) == false)
//{
//Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
//return;
//}
//break;
//
//case WAIT_TIMEOUT:
//// Continue waiting
//continue;
//
//case WAIT_FAILED:
//Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
//return;
//}*/
////void FileChangeWatcher::ThreadFunction(std::wstring aDirectoryToWatch, std::atomic<bool> *stopThreadFlag)
////{
//	
//
////	/*HANDLE waitHandle = FindFirstChangeNotification(aDirectoryToWatch.c_str(), true, FILE_NOTIFY_CHANGE_LAST_WRITE);
////
////	if (waitHandle == INVALID_HANDLE_VALUE)
////	{
////		Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
////		return;
////	}*/
////
////	FILE_NOTIFY_INFORMATION notifications[255];
////
////	while (stopThreadFlag->load() == false)
////	{
////		/*DWORD waitStatus = WaitForSingleObject(waitHandle, 250);
////
////		switch (waitStatus)
////		{
////		case WAIT_OBJECT_0:
////			if (FindNextChangeNotification(waitHandle) == false)
////			{
////				Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
////				return;
////			}
////			break;
////
////		case WAIT_TIMEOUT:
////			// Continue waiting
////			continue;
////
////		case WAIT_FAILED:
////			Warning("FileChangeWatcher failed, you will not be notified of changes to the directory.");
////			return;
////		}*/
////
////		FILE_NOTIFY_INFORMATION * current = notifications;
////		DWORD bytesReturned;
////
////		if (ReadDirectoryChangesW(directory, notifications, sizeof(notifications), true, FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, nullptr, nullptr))
////		{
////			if (stopThreadFlag->load() == true)
////			{
////				return;
////			}
////
////			for (;;)
////			{
////				std::vector<wchar_t> data;
////				data.resize(current->FileNameLength + sizeof(wchar_t));
////				memcpy(&data[0], current->FileName, current->FileNameLength);
////				data[data.size() - sizeof(wchar_t)] = L'\0';
////
////				std::string fileName;
////
////				if (myFormat == FileChangeWatcherNotificationFormat::eDefault)
////				{
////					fileName = std::string(data.begin(), data.end());
////				}
////				else
////				{
////					fileName.resize((data.size() / sizeof(wchar_t)) - 1);
////
////					for (size_t i = 0; i < fileName.size(); i++)
////					{
////						if (data[i] == L'\\')
////						{
////							if (myFormat == FileChangeWatcherNotificationFormat::eForwardSlashes)
////							{
////								fileName[i] = '/';
////								continue;;
////							}
////						}
////						else if (data[i] == '/')
////						{
////							if (myFormat == FileChangeWatcherNotificationFormat::eBackSlashes)
////							{
////								fileName[i] = '\\';
////								continue;
////							}
////						}
////
////						fileName[i] = static_cast<char>(data[i]);
////					}
////				}
////
////				auto currentTime = myWatch.GetElapsedTime().InSeconds();
////				auto &&lastTimeIt = lastTime.find(fileName);
////
////				if (lastTime.find(fileName) == lastTime.end() ||
////					currentTime > lastTimeIt->second + myMinimumTimeDifference)
////				{
////					std::lock_guard<std::mutex> lock(myMutex);
////
////					myChanges.push_back(ChangeEntry
////					{
////						currentTime + 0.2f,
////						fileName
////					});
////
////					lastTime[fileName] = currentTime;
////				}
////
////				if (current->NextEntryOffset == 0)
////				{
////					break;
////				}
////
////				current = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(reinterpret_cast<char*>(current) + current->NextEntryOffset);
////			}
////		}
////		else
////		{
////			Sleep(250);
////		}
////	}
////
////	//FindCloseChangeNotification(waitHandle);
////}
//
