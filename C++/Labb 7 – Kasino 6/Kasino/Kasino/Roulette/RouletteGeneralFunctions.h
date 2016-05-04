#pragma once
#include "..\KasinoGeneralFunctions.h"

namespace Kasino {
namespace Roullete {
namespace General {

enum class enumRouletteBetTypes 
{
	eSingle = 1,
	eSplit,
	eStreet,
	eCorner,
	eDoubleStreet,
	eManque,
	ePasse,
	eRedOrBlack,
	EvenorOdd,
	DozenBet,
	Column,
	enumLenght
};

enum class enumRouletteColumn
{
	eLeftColumn,
	eMiddleColumn,
	eRightColumn
};

enum class enumRouletteColor
{
	eBlack,
	eRed,
	enumLength
};

enum class enumDozenTypes
{
	e1_12Premiere,
	e13_24Moyenne,
	e25_36Dernière,
	enumLength
};

int RollRoulleteBall();

float GetRouletteOddsFormula(const int aUserSquaresBetOn);

int GetRowFromSquare(const int aSquareToCheck);

int GetColumnFromSquare(const int aSquareToCheck);

enumRouletteColor GetColorFromSquare(const int aSquareToCheck);

enumDozenTypes GetDozenTypeFromSquare(const int aSquareToCheck);

int GetColorValueFromSquareValue(const int aSquareToCheck);

std::string GetStringRouletteColorFromEnum(const enumRouletteColor aColorToCheck);

std::string GetStringRouletteColumnFromEnum(const enumRouletteColumn aColumnToCheck);

std::string GetStringRouletteOddOrEven(const int aNumberToCheck);

std::string GetStringRouletteDozenType(const enumDozenTypes aTypeToCheck);

enumRouletteColumn CheckForRouletteColumn(const int aSquareToCheckColumn);

}
}
}
