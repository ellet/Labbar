#include "stdafx.h"
#include "Model/HUGModelLoader.h"
#include "Model/DXModel.h"
#include "Model/FBXLoader/FBXLoader.h"

CHUGModelLoader::CHUGModelLoader()
{
	myLoader = new CFBXLoader();
}

CHUGModelLoader::~CHUGModelLoader()
{
}

CDXModel & CHUGModelLoader::CreateCube(const CU::Vector3f & aScale /*= CU::Vector3f::One*/)
{
	CU::GrowingArray<CDXModel::Vertex> prettyVertices;

	prettyVertices.Init(8);
	prettyVertices.Resize(8);

	//TOP
	prettyVertices[0].myPosition.x = (-0.5f * aScale.x);
	prettyVertices[0].myPosition.y = (0.5f * aScale.y);
	prettyVertices[0].myPosition.z = (-0.5f * aScale.z);
	prettyVertices[0].myPosition.w = 1.0f;

	prettyVertices[0].myUV.u = 0.0f;
	prettyVertices[0].myUV.v = 0.0f;


	prettyVertices[1].myPosition.x = (-0.5f * aScale.x);
	prettyVertices[1].myPosition.y = (0.5f * aScale.y);
	prettyVertices[1].myPosition.z = (0.5f * aScale.z);
	prettyVertices[1].myPosition.w = 1.0f;

	prettyVertices[1].myUV.u = 1.0f;
	prettyVertices[1].myUV.v = 0.0f;


	prettyVertices[2].myPosition.x = (0.5f  * aScale.x);
	prettyVertices[2].myPosition.y = (0.5f * aScale.y);
	prettyVertices[2].myPosition.z = (0.5f * aScale.z);
	prettyVertices[2].myPosition.w = 1.0f;

	prettyVertices[2].myUV.u = 0.0f;
	prettyVertices[2].myUV.v = 0.0f;


	prettyVertices[3].myPosition.x = (0.5f  * aScale.x);
	prettyVertices[3].myPosition.y = (0.5f * aScale.y);
	prettyVertices[3].myPosition.z = (-0.5f* aScale.z);
	prettyVertices[3].myPosition.w = 1.0f;

	prettyVertices[3].myUV.u = 1.0f;
	prettyVertices[3].myUV.v = 0.0f;

	// BOT
	prettyVertices[4].myPosition.x = (-0.5f  * aScale.x);
	prettyVertices[4].myPosition.y = (-0.5f * aScale.y);
	prettyVertices[4].myPosition.z = (-0.5f * aScale.z);
	prettyVertices[4].myPosition.w = 1.0f;

	prettyVertices[4].myUV.u = 0.0f;
	prettyVertices[4].myUV.v = 1.0f;


	prettyVertices[5].myPosition.x = (-0.5f * aScale.x);
	prettyVertices[5].myPosition.y = (-0.5f* aScale.y);
	prettyVertices[5].myPosition.z = (0.5f * aScale.z);
	prettyVertices[5].myPosition.w = 1.0f;

	prettyVertices[5].myUV.u = 1.0f;
	prettyVertices[5].myUV.v = 1.0f;


	prettyVertices[6].myPosition.x = (0.5f  * aScale.x);
	prettyVertices[6].myPosition.y = (-0.5f* aScale.y);
	prettyVertices[6].myPosition.z = (0.5f * aScale.z);
	prettyVertices[6].myPosition.w = 1.0f;


	prettyVertices[6].myUV.u = 0.0f;
	prettyVertices[6].myUV.v = 1.0f;


	prettyVertices[7].myPosition.x = (0.5f  * aScale.x);
	prettyVertices[7].myPosition.y = (-0.5f* aScale.y);
	prettyVertices[7].myPosition.z = (-0.5f* aScale.z);
	prettyVertices[7].myPosition.w = 1.0f;


	prettyVertices[7].myUV.u = 1.0f;
	prettyVertices[7].myUV.v = 1.0f;

	CU::GrowingArray<unsigned int> prettyIndexes;
	prettyIndexes.Init(64);
	prettyIndexes.Resize(36);

	prettyIndexes[0] = 0;
	prettyIndexes[1] = 1;
	prettyIndexes[2] = 2;
	prettyIndexes[3] = 0;
	prettyIndexes[4] = 2;
	prettyIndexes[5] = 3;

	prettyIndexes[6] = 4;
	prettyIndexes[7] = 6;
	prettyIndexes[8] = 5;
	prettyIndexes[9] = 4;
	prettyIndexes[10] = 7;
	prettyIndexes[11] = 6;

	prettyIndexes[12] = 4;
	prettyIndexes[13] = 5;
	prettyIndexes[14] = 1;
	prettyIndexes[15] = 4;
	prettyIndexes[16] = 1;
	prettyIndexes[17] = 0;

	prettyIndexes[18] = 6;
	prettyIndexes[19] = 7;
	prettyIndexes[20] = 3;
	prettyIndexes[21] = 6;
	prettyIndexes[22] = 3;
	prettyIndexes[23] = 2;

	prettyIndexes[24] = 4;
	prettyIndexes[25] = 0;
	prettyIndexes[26] = 3;
	prettyIndexes[27] = 4;
	prettyIndexes[28] = 3;
	prettyIndexes[29] = 7;

	prettyIndexes[30] = 6;
	prettyIndexes[31] = 2;
	prettyIndexes[32] = 1;
	prettyIndexes[33] = 6;
	prettyIndexes[34] = 1;
	prettyIndexes[35] = 5;

	CDXModel * tempModel = new CDXModel();
	tempModel->SetVertices(prettyVertices);
	tempModel->SetIndexes(prettyIndexes);
	tempModel->Init();

	return *tempModel;
}

CDXModel & CHUGModelLoader::CreateModel(const std::string & aFilePath, CU::GrowingArray<std::string> & aTextureFilePaths)
{
	CLoaderModel * prettyLoaderModel = nullptr;
	prettyLoaderModel = myLoader->LoadModel(aFilePath.c_str());

	DL_ASSERT(prettyLoaderModel != nullptr, std::string("Failed To Load Model : " + aFilePath).c_str());
	DL_PRINT(std::string("Loaded Model : " + aFilePath).c_str());

	for (unsigned int iTexture = 0; iTexture < prettyLoaderModel->myTextures.size(); ++iTexture)
	{
		aTextureFilePaths.Add(prettyLoaderModel->myTextures[iTexture]);
	}

	CDXModel * prettyModel = new CDXModel();
	prettyModel->InitWithModel(*prettyLoaderModel);

	return *prettyModel;
}
