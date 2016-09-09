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
	prettyVertices[0].myPosition.x = -0.9f;
	prettyVertices[0].myPosition.y = -0.5f;
	prettyVertices[0].myPosition.z = 0.5f;
	prettyVertices[0].myPosition.w = 1.f;

	prettyVertices[0].myColor.r = 0.0f;
	prettyVertices[0].myColor.g = 1.0f;
	prettyVertices[0].myColor.b = 0.0f;
	prettyVertices[0].myColor.a = 1.f;

	prettyVertices[1].myPosition.x = -0.9f;
	prettyVertices[1].myPosition.y = 0.5f;
	prettyVertices[1].myPosition.z = 0.5f;
	prettyVertices[1].myPosition.w = 1.f;

	prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.f;

	prettyVertices[2].myPosition.x = -0.2f;
	prettyVertices[2].myPosition.y = -0.5f;
	prettyVertices[2].myPosition.z = 0.5f;
	prettyVertices[2].myPosition.w = 1.f;

	prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.f;

	prettyVertices[3].myPosition.x = -0.2f;
	prettyVertices[3].myPosition.y = 0.5f;
	prettyVertices[3].myPosition.z = 0.5f;
	prettyVertices[3].myPosition.w = 1.f;

	prettyVertices[3].myColor.r = 1.0f;
	prettyVertices[3].myColor.g = 1.0f;
	prettyVertices[3].myColor.b = 0.0f;
	prettyVertices[3].myColor.a = 1.f;

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

	prettyVertices[1].myPosition.x = 0.0f;
	prettyVertices[1].myPosition.y = 0.5f;
	prettyVertices[1].myPosition.z = 0.5f;
	prettyVertices[1].myPosition.w = 1.f;

	prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.f;

	prettyVertices[2].myPosition.x = 0.5f;
	prettyVertices[2].myPosition.y = -0.5f;
	prettyVertices[2].myPosition.z = 0.5f;
	prettyVertices[2].myPosition.w = 1.f;

	prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.f;

	CDXModel * tempModel = new CDXModel();
	tempModel->SetVertices(prettyVertices);
	tempModel->Init();

	return *tempModel;
}
