#include "WrapperClass.h"
 


WrapperClass::WrapperClass()
{
	myCard = new CeePlusPlusClass();
}

WrapperClass::~WrapperClass()
{
	delete myCard;
	myCard = nullptr;
}

void WrapperClass::SetApaToCard(const int aNumber)
{
	myCard->SetApa(aNumber);
}

int WrapperClass::GetApaFromCard()
{
	return myCard->GetApa();
}

