#pragma once
#include "KasinoGeneralFunctions.h"

namespace Kasino {
namespace Games {

enum class enumLessAndMore
{
	eLess = 1,
	eMore = 2
};

void GuessMoreOrLess(float & aUserMoney, float & aTableStanding);

}
}
