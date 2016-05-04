//#include <iostream>
//#include <Macros.h>
#include "testTimmers.h"
#include "../CommonUtilities/Timer/TimeManager.h"
int main()
{
	CommonUtilities::TimeManager::Create();

	testTimmers Test;

	Test.doTimerTest();
}