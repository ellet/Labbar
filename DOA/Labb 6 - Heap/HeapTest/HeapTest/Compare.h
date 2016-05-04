#ifndef COMPARE_H
#define COMPARE_H

template <typename T>
class Compare
{
public:
	Compare();
	~Compare();
	virtual bool CompareValues(T aFirst, T aSecond) = 0;


};

template <typename T>
Compare<T>::Compare()
{
	
}

template <typename T>
Compare<T>::~Compare()
{
	
}


#endif