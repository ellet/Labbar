#pragma once
#include <atomic>
#include <thread>


class ConsoleInputHandler
{
public:
	ConsoleInputHandler();
	~ConsoleInputHandler();

	void Start(const std::string & aClientName);
	void Stop();

	bool GetInputString( std::string & aStringToSet );

private:
	std::string myClientName;
	std::string myString;
	std::atomic<bool> myIsDone;
	std::atomic<bool> myIsAlive;

	std::thread * myThread;

	void ThreadUpdate();
};

