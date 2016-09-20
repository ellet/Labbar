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
	myModel = &CHUGEngineSingleton::GetModel();
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

void CHUGModel::Render()
{
	CU::GrowingArray<CU::Vector3f>tgaPosition;
	tgaPosition.Init(29);

	tgaPosition.Add(CU::Vector3f(-8.f, 4.f, 0));
	tgaPosition.Add(CU::Vector3f(-10.f, 4.f, 0));
	tgaPosition.Add(CU::Vector3f(-6.f, 4.f, 0));

	tgaPosition.Add(CU::Vector3f(-8.f, 2.f, 0));
	tgaPosition.Add(CU::Vector3f(-8.f, 0.f, 0));
	tgaPosition.Add(CU::Vector3f(-8.f, -2.f, 0));



	tgaPosition.Add(CU::Vector3f(0.f, 4.f, 0));
	tgaPosition.Add(CU::Vector3f(2.f, 4.f, 0));
	tgaPosition.Add(CU::Vector3f(4.f, 4.f, 0));

	tgaPosition.Add(CU::Vector3f(0.f, 2.f, 0));
	tgaPosition.Add(CU::Vector3f(0.f, 0.f, 0));
	tgaPosition.Add(CU::Vector3f(0.f, -2.f, 0));



	tgaPosition.Add(CU::Vector3f(2.f, -2.f, 0));
	tgaPosition.Add(CU::Vector3f(4.f, -2.f, 0));
	tgaPosition.Add(CU::Vector3f(4.f, 0.f, 0));


	tgaPosition.Add(CU::Vector3f(12.f, 4.f, 0));
	tgaPosition.Add(CU::Vector3f(14.f, 2.f, 0));
	tgaPosition.Add(CU::Vector3f(10.f, 2.f, 0));

	tgaPosition.Add(CU::Vector3f(10.f, 0.f, 0));
	tgaPosition.Add(CU::Vector3f(10.f, -2.f, 0));
	tgaPosition.Add(CU::Vector3f(14.f, 0.f, 0));

	tgaPosition.Add(CU::Vector3f(14.f, -2.f, 0));
	tgaPosition.Add(CU::Vector3f(12.f, 0.f, 0));

	for (unsigned short iPosition = 0; iPosition < tgaPosition.Size(); ++iPosition)
	{
		myTransformation.SetPosition(tgaPosition[iPosition]);
		myModel->Render(myTransformation);
	}
}