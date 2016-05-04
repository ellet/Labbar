#include "stdafx.h"
#include "ThreadPrimes.h"
#include <iostream>
#include <chrono>


ThreadPrimes::ThreadPrimes(const size_t aThreadCount)
{
	myNumbersCheckedCounter = 3;
	myVectorOfPrimes.push_back(2);
	myRunStill = true;

	for (size_t iThreads = 0; iThreads < aThreadCount; ++iThreads)
	{
		myThreads.push_back(new std::thread(&ThreadPrimes::ThreadLoop, this, &myResultVectorLock));
	}
	myPrintThread = new std::thread(&ThreadPrimes::PrintPrimeLoop, this, &myResultVectorLock);
}


ThreadPrimes::~ThreadPrimes()
{
	for (size_t iThreads = 0; iThreads < myThreads.size(); ++iThreads)
	{
		delete myThreads[iThreads];
		myThreads[iThreads] = nullptr;
	}
}


void ThreadPrimes::EndCount()
{
	myRunStill = false;
}

void ThreadPrimes::CheckAllThreadsEnded()
{
	for (size_t iThreads = 0; iThreads < myThreads.size(); ++iThreads)
	{
		myThreads[iThreads]->join();
	}
	myPrintThread->join();
}

bool ThreadPrimes::CheckIfPrime(_Longlong aNumber)
{
	size_t numberToCountTo = aNumber / 2;

	for (size_t iCount = 2; iCount <= numberToCountTo; ++iCount)
	{
		if (aNumber % iCount == 0)
		{
			return false;
		}
	}

	return true;
}

void ThreadPrimes::AddResultToResultVector(std::mutex * aResultLock, const _Longlong & aResult)
{
	aResultLock->lock();

	myVectorOfPrimes.push_back(aResult);

	aResultLock->unlock();
}

void ThreadPrimes::ThreadLoop(std::mutex * aResultLock)
{
	while (myRunStill == true)
	{
		_Longlong currentNumber = ++myNumbersCheckedCounter;
		if (CheckIfPrime(currentNumber) == true)
		{
			AddResultToResultVector(aResultLock, currentNumber);
		}
	}
}

void ThreadPrimes::PrintPrimeLoop(std::mutex * aResultLock)
{
	std::vector<_Longlong> printVector;

	size_t printedNumbers = 0;
	while (myRunStill == true)
	{
		GetVectorForPrint(aResultLock, printVector);
		for (; printedNumbers < printVector.size(); ++printedNumbers)
		{
			std::cout << printVector[printedNumbers] << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void ThreadPrimes::GetVectorForPrint(std::mutex * aResultLock, std::vector<_Longlong> & aVectorToSet)
{
	aResultLock->lock();

	aVectorToSet = myVectorOfPrimes;

	aResultLock->unlock();
}

//if (CheckIfPrime(numberCount) == true)
//{
//	vectorOfPrimes.push_back(numberCount);
//}
//
//++numberCount;
//
//
//for (size_t iPrime = 0; iPrime < vectorOfPrimes.size(); ++iPrime)
//{
//	std::cout << vectorOfPrimes[iPrime] << std::endl;
//}