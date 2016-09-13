#include "stdafx.h"
#include "Model/HUGModel.h"
#include "Model/DXModel.h"
#include "Model/HUGModelLoader.h"
#include "Model/Texture/HUGTexture.h"
#include "Effect/HUGEffect.h"
#include "Camera/HUGCameraInterface.h"
#include "Engine/HUGEngine.h"
#include "HUGFramework/HUGDXFramework.h"

CHUGModel::CHUGModel()
{
	myModel = nullptr;
	myTexture = nullptr;
}


CHUGModel::~CHUGModel()
{
	//myTexture->Release();
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

void CHUGModel::InitAsCube(const CU::Vector3f & aPosition /*= CU::Vector3f::Zero*/, const CU::Vector3f & aScale /*= CU::Vector3f::One*/)
{
	CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateCube(aScale);
	myTransformation.SetPosition(aPosition);
	Init();
}

void CHUGModel::Init()
{
	myTexture = new CHUGTexture();
	myTexture->Init(&CHUGEngineSingleton::GetFramework().GetDevice(), &CHUGEngineSingleton::GetFramework().GetDeviceContext(), "meh");
	myModel->Init();
}

void CHUGModel::Render(const CHUGCameraInterface & aCamera)
{
	CHUGEffect::MatrixBufferType tempMatrixes;
	tempMatrixes.myToWorld = myTransformation;
	tempMatrixes.myToCamera = aCamera.GetCameraMatrix().GetInverse();
	tempMatrixes.myToProjection = aCamera.GetProjection();
	myModel->Render(tempMatrixes.myToWorld, tempMatrixes.myToCamera, tempMatrixes.myToProjection, myTexture->GetTexture());
}

void CHUGModel::Rotate()
{
	const float fakeDeltaTime = 0.0001f;
	const float fakeSpeedY = 10.f;
	const float fakeSpeedZ = 5.f;

	myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundY(DEGRESS_TO_RADIANSF(fakeSpeedY * fakeDeltaTime));
	myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundZ(DEGRESS_TO_RADIANSF(fakeSpeedZ * fakeDeltaTime));
}

void CHUGModel::SetPosition(const CU::Vector3f & aPosition /*= CU::Vector3f::Zero*/)
{
	myTransformation.SetPosition(aPosition);
}
