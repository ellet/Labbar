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

void CHUGModel::InitAsCube()
{
	CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateCube();
}

void CHUGModel::Init()
{
	myModel->Init();
}

void CHUGModel::Update(const CU::Time & aDeltaTime)
{
	const float DeltaTime = aDeltaTime.GetSeconds();

	float rotatespeed = 10.f;

	myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundY(DEGRESS_TO_RADIANSF(rotatespeed * DeltaTime));
	//myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundX(DEGRESS_TO_RADIANSF(rotatespeed * fakeDeltaTime));
}

void CHUGModel::Render(const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform)
{
	CU::Matrix44f tempMatrix = myTransformation;
	for (int iTestDraw = 0; iTestDraw < 1000000; ++iTestDraw)
	{
		const float tempX = myRandomizer.GetRandomValue(-0.5f, 0.5f);
		const float tempY = myRandomizer.GetRandomValue(-0.5f, 0.5f);
		const float tempZ = myRandomizer.GetRandomValue(-0.5f, 0.5f);

		CU::Vector3f tempVector(tempX, tempY, tempZ);

		tempMatrix.SetPosition(myTransformation.GetPosition() + tempVector);
		myModel->Render(tempMatrix, aCameraTransform, aProjectionTransform);
	}
}