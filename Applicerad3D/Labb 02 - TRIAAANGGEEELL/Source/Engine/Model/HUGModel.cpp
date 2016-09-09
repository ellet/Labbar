#include "stdafx.h"
#include "Model/HUGModel.h"
#include "Model/DXModel.h"
#include "Model/HUGModelLoader.h"

CHUGModel::CHUGModel()
{
	myModel = nullptr;
}


CHUGModel::~CHUGModel()
{
	SAFE_DELETE(myModel);
}

void CHUGModel::InitAsTriangle()
{
	CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateTriangle();
}

void CHUGModel::InitAsQuad()
{
	CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateQuad();
}

void CHUGModel::Init()
{
	myModel->Init();
}

void CHUGModel::Render()
{
	myModel->Render();
}