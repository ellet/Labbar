#include "stdafx.h"
#include "HUGModel.h"
#include "DXModel.h"

CHUGModel::CHUGModel()
{
	myModel = new CDXModel();
}


CHUGModel::~CHUGModel()
{
	SAFE_DELETE(myModel);
}

void CHUGModel::Init()
{
	myModel->Init();
}

void CHUGModel::Render()
{
	myModel->Render();
}