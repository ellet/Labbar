#ifndef LESSER_H
#define LESSER_H

#include "Compare.h"

template <typename T>
class Lesser: public Compare<T>
{
public:
	Lesser();
	~Lesser();
	bool CompareValues(T aFirst, T aSecond) override;
};

template <typename T>
Lesser<T>::Lesser()
{
	
}

template <typename T>
Lesser<T>::~Lesser()
{
	
}

template <typename T>
bool Lesser<T>::CompareValues(T aFirst, T aSecond)
{
	return (aFirst < aSecond);
}

#endif