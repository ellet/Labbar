#include "CeePlusPlusClass.h"



CeePlusPlusClass::CeePlusPlusClass()
{
	myApa = 0;
	myText = "Derp";
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

void CeePlusPlusClass::SetText(const std::string & aTexty)
{
	myText = aTexty;
}

const std::string & CeePlusPlusClass::GetTexty()
{
	return myText;
}
