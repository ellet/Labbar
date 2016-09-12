#include "stdafx.h"
#include "Model/HUGModelLoader.h"
#include "Model/DXModel.h"

CHUGModelLoader::CHUGModelLoader()
{
}


CHUGModelLoader::~CHUGModelLoader()
{
}

CDXModel & CHUGModelLoader::CreateQuad()
{
	CU::GrowingArray<CDXModel::Vertex> prettyVertices;
	prettyVertices.Init(4);
	prettyVertices.Resize(4);
	prettyVertices[0].myPosition.x = -1.0f;
	prettyVertices[0].myPosition.y = -1.0f;
	prettyVertices[0].myPosition.z = 0.5f;
	prettyVertices[0].myPosition.w = 1.f;

	prettyVertices[0].myColor.r = 0.0f;
	prettyVertices[0].myColor.g = 1.0f;
	prettyVertices[0].myColor.b = 0.0f;
	prettyVertices[0].myColor.a = 1.f;

	prettyVertices[0].myUV.u = 0.0f;
	prettyVertices[0].myUV.v = 0.0f;

	prettyVertices[1].myPosition.x = -1.0f;
	prettyVertices[1].myPosition.y = 1.0f;
	prettyVertices[1].myPosition.z = 0.5f;
	prettyVertices[1].myPosition.w = 1.f;

	prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.f;

	prettyVertices[1].myUV.u = 0.0f;
	prettyVertices[1].myUV.v = 0.0f;

	prettyVertices[2].myPosition.x = 1.0f;
	prettyVertices[2].myPosition.y = -1.0f;
	prettyVertices[2].myPosition.z = 0.5f;
	prettyVertices[2].myPosition.w = 1.f;

	prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.f;

	prettyVertices[2].myUV.u = 0.0f;
	prettyVertices[2].myUV.v = 0.0f;

	prettyVertices[3].myPosition.x = 1.0f;
	prettyVertices[3].myPosition.y = 1.0f;
	prettyVertices[3].myPosition.z = 0.5f;
	prettyVertices[3].myPosition.w = 1.f;

	prettyVertices[3].myColor.r = 1.0f;
	prettyVertices[3].myColor.g = 1.0f;
	prettyVertices[3].myColor.b = 0.0f;
	prettyVertices[3].myColor.a = 1.f;

	prettyVertices[3].myUV.u = 0.0f;
	prettyVertices[3].myUV.v = 0.0f;

	CDXModel * tempModel = new CDXModel();
	tempModel->SetVertices(prettyVertices);
	tempModel->Init();

	return *tempModel;
}

CDXModel & CHUGModelLoader::CreateTriangle()
{
	CU::GrowingArray<CDXModel::Vertex> prettyVertices;
	prettyVertices.Init(4);
	prettyVertices.Resize(3);
	prettyVertices[0].myPosition.x = 0.0f;
	prettyVertices[0].myPosition.y = -0.5f;
	prettyVertices[0].myPosition.z = 0.5f;
	prettyVertices[0].myPosition.w = 1.f;

	prettyVertices[0].myColor.r = 0.0f;
	prettyVertices[0].myColor.g = 1.0f;
	prettyVertices[0].myColor.b = 0.0f;
	prettyVertices[0].myColor.a = 1.f;

	prettyVertices[0].myUV.u = 0.0f;
	prettyVertices[0].myUV.v = 0.0f;

	prettyVertices[1].myPosition.x = 0.0f;
	prettyVertices[1].myPosition.y = 0.5f;
	prettyVertices[1].myPosition.z = 0.5f;
	prettyVertices[1].myPosition.w = 1.f;

	prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.f;

	prettyVertices[1].myUV.u = 0.0f;
	prettyVertices[1].myUV.v = 0.0f;

	prettyVertices[2].myPosition.x = 0.5f;
	prettyVertices[2].myPosition.y = -0.5f;
	prettyVertices[2].myPosition.z = 0.5f;
	prettyVertices[2].myPosition.w = 1.f;

	prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.f;

	prettyVertices[3].myUV.u = 0.0f;
	prettyVertices[3].myUV.v = 0.0f;

	CDXModel * tempModel = new CDXModel();
	tempModel->SetVertices(prettyVertices);
	tempModel->Init();

	return *tempModel;
}

CDXModel & CHUGModelLoader::CreateCube()
{
	CU::GrowingArray<CDXModel::Vertex> prettyVertices;
	const float scale = 0.4f;

	prettyVertices.Init(8);
	prettyVertices.Resize(8);

	//TOP
	prettyVertices[0].myPosition.x = -0.5f * scale;
	prettyVertices[0].myPosition.y = 0.5f * scale;
	prettyVertices[0].myPosition.z = -0.5f * scale;
	prettyVertices[0].myPosition.w = 1.0f;

	prettyVertices[0].myColor.r = 1.0f;
	prettyVertices[0].myColor.g = 1.0f;
	prettyVertices[0].myColor.b = 0.0f;
	prettyVertices[0].myColor.a = 1.0f;

	prettyVertices[0].myUV.u = 0.0f;
	prettyVertices[0].myUV.v = 0.0f;


	prettyVertices[1].myPosition.x = -0.5f * scale;
	prettyVertices[1].myPosition.y = 0.5f * scale;
	prettyVertices[1].myPosition.z = 0.5f * scale;
	prettyVertices[1].myPosition.w = 1.0f;

	prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.0f;

	prettyVertices[1].myUV.u = 1.0f;
	prettyVertices[1].myUV.v = 0.0f;


	prettyVertices[2].myPosition.x = 0.5f * scale;
	prettyVertices[2].myPosition.y = 0.5f * scale;
	prettyVertices[2].myPosition.z = 0.5f * scale;
	prettyVertices[2].myPosition.w = 1.0f;

	prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.0f;

	prettyVertices[2].myUV.u = 0.0f;
	prettyVertices[2].myUV.v = 0.0f;


	prettyVertices[3].myPosition.x = 0.5f * scale;
	prettyVertices[3].myPosition.y = 0.5f * scale;
	prettyVertices[3].myPosition.z = -0.5f * scale;
	prettyVertices[3].myPosition.w = 1.0f;

	prettyVertices[3].myColor.r = 0.0f;
	prettyVertices[3].myColor.g = 1.0f;
	prettyVertices[3].myColor.b = 0.0f;
	prettyVertices[3].myColor.a = 1.0f;

	prettyVertices[3].myUV.u = 1.0f;
	prettyVertices[3].myUV.v = 0.0f;

	// BOT
	prettyVertices[4].myPosition.x = -0.5f * scale;
	prettyVertices[4].myPosition.y = -0.5f * scale;
	prettyVertices[4].myPosition.z = -0.5f * scale;
	prettyVertices[4].myPosition.w = 1.0f;

	prettyVertices[4].myColor.r = 1.0f;
	prettyVertices[4].myColor.g = 0.0f;
	prettyVertices[4].myColor.b = 1.0f;
	prettyVertices[4].myColor.a = 1.0f;

	prettyVertices[4].myUV.u = 0.0f;
	prettyVertices[4].myUV.v = 1.0f;


	prettyVertices[5].myPosition.x = -0.5f * scale;
	prettyVertices[5].myPosition.y = -0.5f * scale;
	prettyVertices[5].myPosition.z = 0.5f * scale;
	prettyVertices[5].myPosition.w = 1.0f;

	prettyVertices[5].myColor.r = 1.0f;
	prettyVertices[5].myColor.g = 1.0f;
	prettyVertices[5].myColor.b = 1.0f;
	prettyVertices[5].myColor.a = 1.0f;

	prettyVertices[5].myUV.u = 1.0f;
	prettyVertices[5].myUV.v = 1.0f;


	prettyVertices[6].myPosition.x = 0.5f * scale;
	prettyVertices[6].myPosition.y = -0.5f * scale;
	prettyVertices[6].myPosition.z = 0.5f * scale;
	prettyVertices[6].myPosition.w = 1.0f;

	prettyVertices[6].myColor.r = 1.0f;
	prettyVertices[6].myColor.g = 1.0f;
	prettyVertices[6].myColor.b = 1.0f;
	prettyVertices[6].myColor.a = 1.0f;

	prettyVertices[6].myUV.u = 0.0f;
	prettyVertices[6].myUV.v = 1.0f;


	prettyVertices[7].myPosition.x = 0.5f * scale;
	prettyVertices[7].myPosition.y = -0.5f * scale;
	prettyVertices[7].myPosition.z = -0.5f * scale;
	prettyVertices[7].myPosition.w = 1.0f;

	prettyVertices[7].myColor.r = 1.0f;
	prettyVertices[7].myColor.g = 1.0f;
	prettyVertices[7].myColor.b = 1.0f;
	prettyVertices[7].myColor.a = 1.0f;

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
