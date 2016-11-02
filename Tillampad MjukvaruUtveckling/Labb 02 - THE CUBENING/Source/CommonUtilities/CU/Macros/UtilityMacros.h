#pragma once

#define PIXELTONORM(object, screen) (static_cast<float>(object) * (1.0f/static_cast<float>(screen)))

#define PRINT_VARIABLE(a) std::cout << (#a) << " has " << (a) << std::endl;
#define SWAP(a, b) auto temp = (a); (a) = (b); (b) = (temp);

#define VECTOR_POSITION_SIZE(aVector) ((aVector).size() -1)

#define VECTOR_CYCLE_ERASE(aVector, aPosition) \
assert((aPosition < VECTOR_POSITION_SIZE(aVector) && "Position is out of range") );\
(aVector)[(aPosition)] = (aVector)[VECTOR_POSITION_SIZE(aVector)]; \
(aVector).erase((aVector).end() - 1)