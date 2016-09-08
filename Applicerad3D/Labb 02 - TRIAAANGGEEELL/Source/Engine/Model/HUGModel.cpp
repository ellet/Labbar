#include "stdafx.h"
#include "HUGModel.h"
#include "DXModel.h"

CHUGModel::CHUGModel()
{
	myModel = nullptr;
}


CHUGModel::~CHUGModel()
{
}

void CHUGModel::Init()
{
	myModel->Init();
}

void CHUGModel::Render()
{
	myModel->Render();
}