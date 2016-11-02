#pragma once
#include <vector>
#include <thread>         // std::thread

class CDataRace
{
public:
	CDataRace(unsigned int aThreadNumber);
	~CDataRace();
	void Run();
private:
	std::vector<std::thread*> myThreads;
};

