#include "stdafx.h"
#include "ConsoleFunctions.h"

namespace MyFunctions {
namespace Console {

void DumpCIN()
{
	std::cin.sync();
}

bool AskTrueOrFalse(const std::string aYesNoQuestion)
{
	bool wrongUserInput = true;
	do
	{
		std::cout << std::endl;
		std::cout << aYesNoQuestion << " Y/N" << std::endl;

		char playerPromptInput;
		std::cin >> playerPromptInput;

		DumpCIN();

		if (playerPromptInput == 'Y')
		{
			return true;
		}
		else if (playerPromptInput == 'y')
		{
			return true;
		}
		if (playerPromptInput == 'N')
		{
			return false;
		}
		else if (playerPromptInput == 'n')
		{
			return false;
		}
		else
		{
			std::cout << "Invalid Input" << std::endl << std::endl;
		}
	} while (wrongUserInput);
	return false;
}

int AskForNumber(const std::string aTextQuestionForNumber, const int aMinRange, const int aMaxRange)
{
	int userNumberRespons;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
	} while (userNumberRespons < aMinRange || userNumberRespons > aMaxRange);
	return userNumberRespons;
}

int AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const int aMinRange, const int aMaxRange)
{
	int userNumberRespons;
	bool checkForValidInput;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
		if (userNumberRespons < aMinRange || userNumberRespons > aMaxRange)
		{
			checkForValidInput = true;
			std::cout << aInvalidInputResponse << std::endl;
		}
		else
		{
			checkForValidInput = false;
		}
	} while (checkForValidInput);
	return userNumberRespons;
}

float AskForNumber(const std::string aTextQuestionForNumber, const float aMinRange, const float aMaxRange)
{
	float userNumberRespons;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
	} while (userNumberRespons < aMinRange || userNumberRespons > aMaxRange);
	return userNumberRespons;
}

float AskForNumber(const std::string aTextQuestionForNumber, const std::string aInvalidInputResponse, const float aMinRange, const float aMaxRange)
{
	float userNumberRespons;
	bool checkForValidInput;
	do
	{
		std::cout << aTextQuestionForNumber << std::endl;
		std::cin >> userNumberRespons;
		DumpCIN();
		std::cin.clear();
		if (userNumberRespons < aMinRange || userNumberRespons > aMaxRange)
		{
			checkForValidInput = true;
			std::cout << aInvalidInputResponse << std::endl;
		}
		else
		{
			checkForValidInput = false;
		}
	} while (checkForValidInput);
	return userNumberRespons;
}

}
}