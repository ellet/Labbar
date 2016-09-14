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
	myTextures.Init(1);
}


CHUGModel::~CHUGModel()
{
	SAFE_DELETE(myModel);
}

void CHUGModel::InitAsCube(const CU::Vector3f & aPosition /*= CU::Vector3f::Zero*/, const CU::Vector3f & aScale /*= CU::Vector3f::One*/)
{
	CHUGModelLoader tempLoader;
	myModel = &tempLoader.CreateCube(aScale);
	myTransformation.SetPosition(aPosition);
	InitTexture();
}

void CHUGModel::Init(const std::string & aModelFilePath)
{
	CHUGModelLoader tempLoader;
	CU::GrowingArray<std::string> textureFilePaths;
	textureFilePaths.Init(4);
	
	myModel = &tempLoader.CreateModel(aModelFilePath, textureFilePaths);
	
	/*TODO add support for multiple textures*/
	textureFilePaths[0] = "Sprites/" + textureFilePaths[0];
	InitTexture(textureFilePaths[0]);
}

void CHUGModel::InitTexture(const std::string & aTextureFilepath /*= "Sprites/adam.dds"*/)
{
	myTextures.Add(new CHUGTexture());
	myTextures.GetLast()->Init(&CHUGEngineSingleton::GetFramework().GetDevice(), &CHUGEngineSingleton::GetFramework().GetDeviceContext(), std::wstring(aTextureFilepath.begin(), aTextureFilepath.end()));
}

void CHUGModel::Render(const CHUGCameraInterface & aCamera)
{
	CHUGEffect::MatrixBufferType tempMatrixes;
	tempMatrixes.myToWorld = myTransformation;
	tempMatrixes.myToCamera = aCamera.GetCameraMatrix().GetInverse();
	tempMatrixes.myToProjection = aCamera.GetProjection();
	myModel->Render(tempMatrixes.myToWorld, tempMatrixes.myToCamera, tempMatrixes.myToProjection, myTextures.GetLast()->GetTexture());
}

void CHUGModel::Rotate()
{
	const float fakeSpeedY = 10.f;
	const float fakeSpeedZ = 5.f;

	myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundY(DEGRESS_TO_RADIANSF(fakeSpeedY * GET_DELTA_SECONDS));
	myTransformation = myTransformation * CU::Matrix44f::CreateRotateAroundZ(DEGRESS_TO_RADIANSF(fakeSpeedZ * GET_DELTA_SECONDS));
}

void CHUGModel::SetPosition(const CU::Vector3f & aPosition /*= CU::Vector3f::Zero*/)
{
	myTransformation.SetPosition(aPosition);
}
