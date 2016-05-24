#include "CeePlusPlusClass.h"



CeePlusPlusClass::CeePlusPlusClass()
{
	myApa = 0;
}


CeePlusPlusClass::~CeePlusPlusClass()
{
}

void CeePlusPlusClass::	SetApa(const int aNumber)
{
	myApa = aNumber;
}

int CeePlusPlusClass::GetApa() const
{
	return myApa;
}
