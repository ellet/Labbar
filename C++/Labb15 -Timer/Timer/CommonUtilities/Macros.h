#pragma once
#include <assert.h>

#define PRINT_VARIABLE(a) std::cout << (#a) << " has " << (a) << std::endl;

#define VECTOR_POSITION_SIZE(aVector) ((aVector).size() -1)

#define SIGN(x) ((x) > 0 ? 1:((x)<0 ?-1:0)

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define SAFE_DELETE(a) delete (a); (a) = nullptr;

#define SWAP(a, b) auto temp = (a); (a) = (b); (b) = (temp);

#define CLAMP(a, b, c) MAX(b, MIN(a,c))

#define VECTOR_CYCLE_ERASE(aVector, aPosition) \
assert((aPosition < VECTOR_POSITION_SIZE(aVector) && "Position is out of range") );\
(aVector)[(aPosition)] = (aVector)[VECTOR_POSITION_SIZE(aVector)]; \
(aVector).erase((aVector).end() - 1)
/*
(aPosition < VECTORPOSITIONSIZE(aVector)) ? (assert) ((aVector)[(aPosition)] = (aVector)[VECTORPOSITIONSIZE(aVector)]) : ((void)0);\
(aPosition < VECTORPOSITIONSIZE(aVector)) ? ((aVector).erase((aVector).end() - 1)) : ((void)0)*/