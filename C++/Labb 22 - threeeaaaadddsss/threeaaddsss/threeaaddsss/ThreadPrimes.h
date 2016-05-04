#pragma once
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

class ThreadPrimes
{
public:
	ThreadPrimes(const size_t aThreadCount);
	~ThreadPrimes();

	void EndCount();

	void CheckAllThreadsEnded();

private:
	void ThreadLoop(std::mutex * aResultLock);
	void PrintPrimeLoop(std::mutex * aResultLock);
	
	void AddResultToResultVector(std::mutex * aResultLock, const _Longlong & aResult);

	void GetVectorForPrint(std::mutex * aResultLock, std::vector<_Longlong> & aVectorToSet);

	bool CheckIfPrime(_Longlong aNumber);

	bool myRunStill;

	std::mutex myResultVectorLock;

	std::atomic<_Longlong> myNumbersCheckedCounter;
	std::vector<_Longlong> myVectorOfPrimes;
	std::vector<std::thread*> myThreads;
	std::thread* myPrintThread;
};

