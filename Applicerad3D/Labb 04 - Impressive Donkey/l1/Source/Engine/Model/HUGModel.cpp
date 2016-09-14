#include "stdafx.h"
#include "Model/HUGModel.h"
#include "Model/DXModel.h"
#include "Model/HUGModelLoader.h"
#include "Engine/HUGEngine.h"

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
	/*CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateTriangle();*/
}

void CHUGModel::InitAsQuad()
{
	/*CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateQuad();*/
}

void CHUGModel::InitAsCube()
{
	/*CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateCube();*/
}

void CHUGModel::InitAsModel(const std::string & aModelFilePath)
{
	
	myModel = &CHUGEngineSingleton::GetModel(aModelFilePath);
}

void CHUGModel::Init()
{
}

void CHUGModel::Update(const CU::Time & aDeltaTime)
{
	const float fakeDeltaTime = aDeltaTime.GetSeconds();

	float rotatespeed = 10.f;

	myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundY(DEGRESS_TO_RADIANSF(rotatespeed * fakeDeltaTime));
	//myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundX(DEGRESS_TO_RADIANSF(rotatespeed * fakeDeltaTime));
}

void CHUGModel::Render(const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform)
{
	myModel->Render(myTransformation, aCameraTransform, aProjectionTransform);
}