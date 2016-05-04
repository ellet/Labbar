#include "stdafx.h"
#include "RouletteGeneralFunctions.h"

namespace Kasino {
namespace Roullete {
namespace General {
float GetRouletteOddsFormula(const int aUserSquaresBetOn)
{
	return ((36.0f / aUserSquaresBetOn) - 1.0f);
}

Kasino::Roullete::General::enumRouletteColumn CheckForRouletteColumn(const int aSquareToCheckColumn)
{
	switch (Kasino::Roullete::General::GetColumnFromSquare(aSquareToCheckColumn))
	{
	case 3:
	{
		return Kasino::Roullete::General::enumRouletteColumn::eRightColumn;
		break;
	}
	case 1:
	{
		return Kasino::Roullete::General::enumRouletteColumn::eLeftColumn;
		break;
	}
	case 2:
	{
		return Kasino::Roullete::General::enumRouletteColumn::eMiddleColumn;
		break;
	}
	default:
	{
		std::cout << "Column Checker FUCKED UP" << std::endl;
		return Kasino::Roullete::General::enumRouletteColumn::eMiddleColumn;
		break;
	}
	}
}

Kasino::Roullete::General::enumDozenTypes GetDozenTypeFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck >= 1 && aSquareToCheck <= 12)
	{
		return Kasino::Roullete::General::enumDozenTypes::e1_12Premiere;
	}
	else if (aSquareToCheck >= 13 && aSquareToCheck <= 24)
	{
		return Kasino::Roullete::General::enumDozenTypes::e13_24Moyenne;
	}
	if (aSquareToCheck >= 25 && aSquareToCheck <= 36)
	{
		return Kasino::Roullete::General::enumDozenTypes::e25_36Dernière;
	}
	else
	{
		std::cout << "DOZEN FROM SQUARE FUKKEN BROKEN" << std::endl;
		return Kasino::Roullete::General::enumDozenTypes::enumLength;
	}
}

Kasino::Roullete::General::enumRouletteColor GetColorFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck == 0)
	{
		return Kasino::Roullete::General::enumRouletteColor::enumLength;
	}
	else if ((aSquareToCheck >= 1 && aSquareToCheck <= 10) || (aSquareToCheck >= 21 && aSquareToCheck <= 28))
	{
		if (MyFunctions::Math::CheckNumberIfEven(aSquareToCheck))
		{
			return Kasino::Roullete::General::enumRouletteColor::eBlack;
		}
		else
		{
			return Kasino::Roullete::General::enumRouletteColor::eRed;
		}
	}
	else
	{
		if (MyFunctions::Math::CheckNumberIfEven(aSquareToCheck))
		{
			return Kasino::Roullete::General::enumRouletteColor::eRed;
		}
		else
		{
			return Kasino::Roullete::General::enumRouletteColor::eBlack;
		}

	}
}

int GetRowFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck == 0)
	{
		return 0;
	}
	else
	{
		return ((aSquareToCheck - 1) / 3) + 1;
	}
}

int GetColumnFromSquare(const int aSquareToCheck)
{
	if (aSquareToCheck == 0)
	{
		return 0;
	}
	return ((aSquareToCheck - 1) % 3) + 1;
}

int GetColorValueFromSquareValue(const int aSquareToCheck)
{
	return static_cast<int>(GetColorFromSquare(aSquareToCheck));
}

std::string GetStringRouletteColorFromEnum(const Kasino::Roullete::General::enumRouletteColor aColorToCheck)
{
	if (aColorToCheck == Kasino::Roullete::General::enumRouletteColor::eBlack)
	{
		return "Black";
	}
	else if (aColorToCheck == Kasino::Roullete::General::enumRouletteColor::eRed)
	{
		return "Red";
	}
	else
	{
		return "ERROR COLOR FUKKEN BROKEN";
	}
}

std::string GetStringRouletteColumnFromEnum(const Kasino::Roullete::General::enumRouletteColumn aColumnToCheck)
{
	if (aColumnToCheck == Kasino::Roullete::General::enumRouletteColumn::eLeftColumn)
	{
		return "Left Column";
	}
	else if (aColumnToCheck == Kasino::Roullete::General::enumRouletteColumn::eRightColumn)
	{
		return "Right Column";
	}
	if (aColumnToCheck == Kasino::Roullete::General::enumRouletteColumn::eMiddleColumn)
	{
		return "Middle Column";
	}
	else
	{
		return "ERROR COLUMN FUKKEN BROKEN";
	}
}

std::string GetStringRouletteOddOrEven(const int aNumberToCheck)
{
	if ((aNumberToCheck % 2) == 0)
	{
		return "Even";
	}
	else
	{
		return "Odd";
	}
}

std::string GetStringRouletteDozenType(const Kasino::Roullete::General::enumDozenTypes aTypeToCheck)
{
	if (aTypeToCheck == Kasino::Roullete::General::enumDozenTypes::e1_12Premiere)
	{
		return "1-12 Premiere";
	}
	else if (aTypeToCheck == Kasino::Roullete::General::enumDozenTypes::e13_24Moyenne)
	{
		return "13-24 Moeyenne";
	}
	else if (aTypeToCheck == Kasino::Roullete::General::enumDozenTypes::e25_36Dernière)
	{
		return "25-36 Dernière";
	}
	else
	{
		return "ERROR DOZEN TYPE FUKKEN BROKEN";
	}
}

int RollRoulleteBall()
{
	std::cout << "Wheel is spinning " << std::endl;
	system("pause");
	std::cout << "Wheel is spinning " << std::endl;
	system("pause");
	std::cout << "Wheel is stopping!" << std::endl;
	system("pause");

	std::cout << std::endl;
	std::cout << std::endl;

	int ballLandedOn = (rand() % (37));
	if (ballLandedOn != 0)
	{
		ballLandedOn -= 1;
	}
	std::cout << "The number is: " << ballLandedOn << std::endl;
	std::cout << "The number is: " << Kasino::Roullete::General::GetStringRouletteOddOrEven(ballLandedOn) << std::endl;
	std::cout << "The row is: " << Kasino::Roullete::General::GetRowFromSquare(ballLandedOn) << std::endl;
	std::cout << "The Dozen is: " << Kasino::Roullete::General::GetStringRouletteDozenType(GetDozenTypeFromSquare(ballLandedOn)) << std::endl;
	std::cout << "The color is: " << Kasino::Roullete::General::GetStringRouletteColorFromEnum(GetColorFromSquare(ballLandedOn)) << std::endl;
	std::cout << "The column is: " << Kasino::Roullete::General::GetStringRouletteColumnFromEnum(CheckForRouletteColumn(ballLandedOn)) << std::endl;

	std::cout << std::endl;
	return ballLandedOn;
}
}
}
}
