#include "testTimmers.h"
#include <Time.h>
//#include "../CommonUtilities/Time.h"
#include "../CommonUtilities/Timer/TimeManager.h"
#include <iostream>
#include <Windows.h>

testTimmers::testTimmers()
{
	myImPaused = false;
	myTestAlarm = CommonUtilities::Alarm(3.f, true);
}


testTimmers::~testTimmers()
{
	CommonUtilities::TimeManager::Destroy();
}

void testTimmers::doTimerTest()
{
	std::cout << "starting loop" << std::endl;

	CommonUtilities::TimeManager::Update();

	/*myFirstTimer = CommonUtilities::TimeManager::CreateNewTimer();
	myDrawTimer = CommonUtilities::TimeManager::CreateNewTimer();
	myFPSTimer = CommonUtilities::TimeManager::CreateNewTimer();*/

	const CommonUtilities::Timer AddCounterTimer;// = CommonUtilities::TimeManager::CreateNewTimer();

	LONGLONG updateCount = 0;
	float timeFPSholder = 0.f;// static_cast<float>(myTimerManager.GetTimerTime(myFPSTimer)->GetSeconds());

	LONGLONG lastDraw = 0;
	LONGLONG lastAdd = 0;
	DrawTimers();

	AddTimer();

	bool testTimmers = true;
	while (testTimmers)
	{
		CommonUtilities::TimeManager::Update();


		++updateCount;
		
		timeFPSholder = myFPSTimer.GetTime().GetSeconds();

		if (myDrawTimer.GetTime().GetSeconds() > lastAdd + 15)
		{
			lastAdd = (myDrawTimer.GetTime().GetSeconds());
			AddTimer();
		}

		if ((myDrawTimer.GetTime().GetMilliSeconds()) > lastDraw + 25)
		{
			lastDraw = ((myDrawTimer.GetTime().GetMilliSeconds()));

			system("CLS");

			std::cout << "have done: " << updateCount << " updates" << std::endl;
			std::cout << "over : " << timeFPSholder << " seconds" << std::endl;
			std::cout << "FPS is: " << (1.f / CommonUtilities::TimeManager::GetDeltaTime()) << std::endl;

			std::cout << "Alarm Progress is: " << myTestAlarm.GetProgress() << std::endl;

			DrawTimers();
		}
	
		Sleep(5);
	}
}

void testTimmers::DrawTimers()
{
	const CommonUtilities::Time & TimeToPrint = myFirstTimer.GetTime();

	std::cout << "Start time is " << CommonUtilities::TimeManager::GetTimeSinceStart() << " seconds" << std::endl;
	
	for (size_t iTimmer = 0; iTimmer < myTimmers.size(); iTimmer++)
	{
		

		std::cout << iTimmer + 1 << " Timmer is: " << myTimmers[iTimmer].GetTime().GetMicroSeconds() << " Microseconds" << std::endl;

		LONGLONG tempVariable = myTimmers[iTimmer].GetTime().GetMicroSeconds();

		std::cout << iTimmer + 1 << " Timmer is: " << myTimmers[iTimmer].GetTime().GetMilliSeconds() << " Milliseconds" << std::endl;
		std::cout << iTimmer + 1 << " Timmer is: " << myTimmers[iTimmer].GetTime().GetSeconds() << " Seconds" << std::endl;
		std::cout << iTimmer + 1 << " Timmer is: " << myTimmers[iTimmer].GetTime().GetMinutes() << " Minutes" << std::endl;
		std::cout << iTimmer + 1 << " Timmer is: " << myTimmers[iTimmer].GetTime().GetHours() << " Hours" << std::endl;
		std::cout << std::endl;
	}
}

void testTimmers::AddTimer()
{
	myTimmers.push_back(CommonUtilities::Timer());
}

