#pragma once
class TestClassAddingNumbers
{
public:
	TestClassAddingNumbers();
	~TestClassAddingNumbers();

	void IncreaseByOne();

	void IncreaseByNumber(const int aNumber);

	int GetTestValue();

private:
	int myTestNumber;
};

inline int TestClassAddingNumbers::GetTestValue()
{
	return myTestNumber;
}