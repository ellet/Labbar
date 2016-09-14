#include "Synchronizer.h"

namespace CommonUtilities
{

	namespace Thread
	{

		template<typename TYPE>
		Synchronizer<TYPE>::Synchronizer()
		{

			myThreads.Init(2);

		}
		template<typename TYPE>
		Synchronizer<TYPE>::~Synchronizer()
		{

			Stop();

		}

		template<typename TYPE>
		inline void Synchronizer<TYPE>::Start()
		{
			myThreads.Optimize();
			for (unsigned short i = 0; i < myThreads.Size(); ++i)
			{
				myThreads[i].Start();
			}
		}
		template<typename TYPE>
		inline void Synchronizer<TYPE>::Run()
		{

			for (unsigned short i = 0; i < myThreads.Size(); ++i)
			{
				myThreads[i].Reset();
			}

			for (unsigned short i = 0; i < myThreads.Size(); ++i)
			{
				while (myThreads[i].IsDone() == false)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}

		}
		template<typename TYPE>
		inline void Synchronizer<TYPE>::Stop()
		{
			if (myThreads.Size() > 0)
			{
				for (unsigned short i = 0; i < myThreads.Size(); ++i)
				{
					myThreads[i].Stop();
				}
				for (unsigned short i = 0; i < myThreads.Size(); ++i)
				{
					myThreads[i].Join();
				}
				myThreads.RemoveAll();
			}
		}

		template<typename TYPE>
		void Synchronizer<TYPE>::AddThreadMethod(functionPointer aFunctionPointer, TYPE &aMember)
		{
			myThreads.Add(ThreadData(aFunctionPointer, aMember));
		}

		template<typename TYPE>
		inline Synchronizer<TYPE>::ThreadData::ThreadData()
		{
			myIsDone = false;
			myIsRunning = true;
		}
		template<typename TYPE>
		inline Synchronizer<TYPE>::ThreadData::ThreadData(functionPointer aFunctionPointer, TYPE &aMember)
		{
			myIsDone = true;
			myIsRunning = true;
			myFunctionPointer = aFunctionPointer;
			myMember = &aMember;
		}
		template<typename TYPE>
		inline Synchronizer<TYPE>::ThreadData::~ThreadData()
		{
			myIsDone = true;
			myIsRunning = false;
		}

		template<typename TYPE>
		inline typename Synchronizer<TYPE>::ThreadData& Synchronizer<TYPE>::ThreadData::operator=(const ThreadData &aSource)
		{
			myIsDone = aSource.myIsDone;
			myIsRunning = aSource.myIsRunning;
			myFunctionPointer = aSource.myFunctionPointer;
			myMember = aSource.myMember;
			return *this;
		}

		template<typename TYPE>
		inline volatile bool Synchronizer<TYPE>::ThreadData::IsDone()
		{
			return myIsDone;
		}
		template<typename TYPE>
		inline void Synchronizer<TYPE>::ThreadData::Start()
		{
			myThread = std::thread(&Synchronizer::ThreadData::Run, this);
		}
		template<typename TYPE>
		inline void Synchronizer<TYPE>::ThreadData::Reset()
		{
			myIsDone = false;
		}
		template<typename TYPE>
		inline void Synchronizer<TYPE>::ThreadData::Stop()
		{
			myIsRunning = false;
		}

		template<typename TYPE>
		inline void Synchronizer<TYPE>::ThreadData::Join()
		{
			myThread.join();
		}

		template<typename TYPE>
		inline void Synchronizer<TYPE>::ThreadData::Run()
		{
			while (myIsRunning == true)
			{
				if (myIsDone == false)
				{
					(myMember->*myFunctionPointer)();
					myIsDone = true;
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}

	}

}
