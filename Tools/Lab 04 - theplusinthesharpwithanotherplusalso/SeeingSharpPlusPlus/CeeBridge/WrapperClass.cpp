#include "WrapperClass.h"
#include <string> 

#include <msclr\marshal_cppstd.h>

using namespace msclr::interop;

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

void WrapperClass::SetTextyToCard(System::String^ aText)
{
	myCard->SetText(marshal_as<std::string>(aText));
}

System::String^ WrapperClass::GetTextyFromCard()
{
	return gcnew System::String(myCard->GetTexty().c_str());
}

