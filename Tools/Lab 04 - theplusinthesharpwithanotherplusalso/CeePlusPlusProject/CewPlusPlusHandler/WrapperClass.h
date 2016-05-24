#pragma once
#include <CeePlusPlusClass.h>


public ref class WrapperClass
{
public:
	WrapperClass();
	~WrapperClass();

	void SetApaToCard(const int aNumber);
	int GetApaFromCard();


private:
	CeePlusPlusClass * myCard;

};

