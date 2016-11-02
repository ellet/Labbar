#pragma once

#include "hge.h"

class HgeSingelton
{
public:
	static void CreateHge();
	static HgeSingelton* GetInstance();
	void Init(HGE* aHge);
	HGE* GetHge();

private:
	HgeSingelton();
	~HgeSingelton();
	HGE* myHge;
	static HgeSingelton* myInstance;

};

#define HGES HgeSingelton::GetInstance()->GetHge()
