#include <iostream>

#include "DataRace.h"
#include "Deadlock.h"

int main()
{
	std::cout << "------------------------------ \n";
	std::cout << "Welcome to the TGA brokenater 2000. Please fix me. \n";
	std::cout << "------------------------------ \n";

	std::cout << "Race condition starting... \n";
	CDataRace dataRace(1000);
	dataRace.Run();
	std::cout << "Race condition finished \n";


	std::cout << "Deadlock test is starting... \n";
	for (int i = 0; i < 5000; i++)
	{
		CDeadlock dl;
		dl.Run();
	}
	std::cout << "Deadlock test is finished... \n";




	std::cout << "Program ended \n";

	int pause = 0;
	std::cin >> pause;
	return 0;
}