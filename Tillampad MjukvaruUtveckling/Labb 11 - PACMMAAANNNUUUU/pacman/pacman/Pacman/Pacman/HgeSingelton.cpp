//#include "StdAfx.h"
#include "HgeSingelton.h"

HgeSingelton* HgeSingelton::myInstance = NULL;

HgeSingelton::HgeSingelton()
{
}

HgeSingelton::~HgeSingelton()
{
}

void HgeSingelton::CreateHge()
{
	myInstance = new HgeSingelton();
}

HgeSingelton* HgeSingelton::GetInstance()
{
	return myInstance;
}

void HgeSingelton::Init(HGE* aHge)
{
	myHge = aHge;
}

HGE* HgeSingelton::GetHge()
{
	return myHge;
}
