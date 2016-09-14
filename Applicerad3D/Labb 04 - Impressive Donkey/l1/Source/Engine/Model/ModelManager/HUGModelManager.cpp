#include "stdafx.h"
#include "HUGModelManager.h"




CHUGModelManager::CHUGModelManager()
{
	
}


CHUGModelManager::~CHUGModelManager()
{
}

CDXModel & CHUGModelManager::CreateQuad()
{
	CU::GrowingArray<CDXModel::Vertex> prettyVertices;
	prettyVertices.Init(4);
	prettyVertices.Resize(4);
	prettyVertices[0].myPosition.x = -1.0f;
	prettyVertices[0].myPosition.y = -1.0f;
	prettyVertices[0].myPosition.z = 0.5f;
	prettyVertices[0].myPosition.w = 1.f;

	/*prettyVertices[0].myColor.r = 0.0f;
	prettyVertices[0].myColor.g = 1.0f;
	prettyVertices[0].myColor.b = 0.0f;
	prettyVertices[0].myColor.a = 1.f;*/

	prettyVertices[1].myPosition.x = -1.0f;
	prettyVertices[1].myPosition.y = 1.0f;
	prettyVertices[1].myPosition.z = 0.5f;
	prettyVertices[1].myPosition.w = 1.f;

	/*prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.f;*/

	prettyVertices[2].myPosition.x = 1.0f;
	prettyVertices[2].myPosition.y = -1.0f;
	prettyVertices[2].myPosition.z = 0.5f;
	prettyVertices[2].myPosition.w = 1.f;

	/*prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.f;*/

	prettyVertices[3].myPosition.x = 1.0f;
	prettyVertices[3].myPosition.y = 1.0f;
	prettyVertices[3].myPosition.z = 0.5f;
	prettyVertices[3].myPosition.w = 1.f;

	/*prettyVertices[3].myColor.r = 1.0f;
	prettyVertices[3].myColor.g = 1.0f;
	prettyVertices[3].myColor.b = 0.0f;
	prettyVertices[3].myColor.a = 1.f;*/

	CDXModel * tempModel = new CDXModel();

	//Todo^^ Edit indices to be correct stuff and not vertex stuff
	/*myIndices.Init(myVertices.Size());
	myIndices.Resize(myVertices.Size());
	*/
	CU::GrowingArray<unsigned int> tempArrayOfIndices;
	tempArrayOfIndices.Init(prettyVertices.Size());
	tempArrayOfIndices.Resize(prettyVertices.Size());

	for (unsigned int i = 0; i < static_cast<unsigned short>(prettyVertices.Size()); ++i)
	{
		tempArrayOfIndices[USHORTCAST(i)] = i;
	}


	tempModel->Init(prettyVertices, tempArrayOfIndices);

	return *tempModel;
}

CDXModel & CHUGModelManager::CreateTriangle()
{
	CU::GrowingArray<CDXModel::Vertex> prettyVertices;
	prettyVertices.Init(4);
	prettyVertices.Resize(3);
	prettyVertices[0].myPosition.x = 0.0f;
	prettyVertices[0].myPosition.y = -0.5f;
	prettyVertices[0].myPosition.z = 0.5f;
	prettyVertices[0].myPosition.w = 1.f;

	/*prettyVertices[0].myColor.r = 0.0f;
	prettyVertices[0].myColor.g = 1.0f;
	prettyVertices[0].myColor.b = 0.0f;
	prettyVertices[0].myColor.a = 1.f;*/

	prettyVertices[1].myPosition.x = 0.0f;
	prettyVertices[1].myPosition.y = 0.5f;
	prettyVertices[1].myPosition.z = 0.5f;
	prettyVertices[1].myPosition.w = 1.f;

	/*prettyVertices[1].myColor.r = 1.0f;
	prettyVertices[1].myColor.g = 0.0f;
	prettyVertices[1].myColor.b = 0.0f;
	prettyVertices[1].myColor.a = 1.f;*/

	prettyVertices[2].myPosition.x = 0.5f;
	prettyVertices[2].myPosition.y = -0.5f;
	prettyVertices[2].myPosition.z = 0.5f;
	prettyVertices[2].myPosition.w = 1.f;

	/*prettyVertices[2].myColor.r = 0.0f;
	prettyVertices[2].myColor.g = 0.0f;
	prettyVertices[2].myColor.b = 1.0f;
	prettyVertices[2].myColor.a = 1.f;*/

	CDXModel * tempModel = new CDXModel();

	CU::GrowingArray<unsigned int> tempArrayOfIndices;
	tempArrayOfIndices.Init(prettyVertices.Size());
	tempArrayOfIndices.Resize(prettyVertices.Size());

	for (unsigned int i = 0; i < static_cast<unsigned short>(prettyVertices.Size()); ++i)
	{
		tempArrayOfIndices[USHORTCAST(i)] = i;
	}

	tempModel->Init(prettyVertices, tempArrayOfIndices);

	return *tempModel;
}

CDXModel & CHUGModelManager::CreateCube()
{
	CU::GrowingArray<CDXModel::Vertex> tempVertices;
	tempVertices.Init(8);
	tempVertices.Resize(8);

	CU::GrowingArray<unsigned int> tempArrayOfIndices;
	tempArrayOfIndices.Init(36);
	tempArrayOfIndices.Resize(36);

	tempVertices[0].myPosition.x = -0.5f;
	tempVertices[0].myPosition.y = 0.5f;
	tempVertices[0].myPosition.z = -0.5f;
	tempVertices[0].myPosition.w = 1.0f;

	/*tempVertices[0].myColor.r = 1.0f;
	tempVertices[0].myColor.g = 1.0f;
	tempVertices[0].myColor.b = 0.0f;
	tempVertices[0].myColor.a = 1.0f;*/

	tempVertices[0].myUV.x = 0.0f;
	tempVertices[0].myUV.y = 0.0f;


	tempVertices[1].myPosition.x = -0.5f;
	tempVertices[1].myPosition.y = 0.5f;
	tempVertices[1].myPosition.z = 0.5f;
	tempVertices[1].myPosition.a = 1.0f;

	/*tempVertices[1].myColor.r = 1.0f;
	tempVertices[1].myColor.g = 0.5f;
	tempVertices[1].myColor.b = 1.0f;
	tempVertices[1].myColor.a = 1.0f;*/

	tempVertices[1].myUV.x = 1.0f;
	tempVertices[1].myUV.y = 0.0f;


	tempVertices[2].myPosition.x = 0.5f;
	tempVertices[2].myPosition.y = 0.5f;
	tempVertices[2].myPosition.z = 0.5f;
	tempVertices[2].myPosition.a = 1.0f;

	/*tempVertices[2].myColor.r = 1.0f;
	tempVertices[2].myColor.g = 1.0f;
	tempVertices[2].myColor.b = 0.0f;
	tempVertices[2].myColor.a = 1.0f;*/

	tempVertices[2].myUV.x = 0.0f;
	tempVertices[2].myUV.y = 0.0f;



	tempVertices[3].myPosition.x = 0.5f;
	tempVertices[3].myPosition.y = 0.5f;
	tempVertices[3].myPosition.z = -0.5f;
	tempVertices[3].myPosition.a = 1.0f;

	/*tempVertices[3].myColor.r = 1.0f;
	tempVertices[3].myColor.g = 1.0f;
	tempVertices[3].myColor.b = 1.0f;
	tempVertices[3].myColor.a = 1.0f;*/

	tempVertices[3].myUV.x = 1.0f;
	tempVertices[3].myUV.y = 0.0f;


	// BOT
	tempVertices[4].myPosition.x = -0.5f;
	tempVertices[4].myPosition.y = -0.5f;
	tempVertices[4].myPosition.z = -0.5f;
	tempVertices[4].myPosition.a = 1.0f;

	/*tempVertices[4].myColor.r = 1.0f;
	tempVertices[4].myColor.g = 0.2f;
	tempVertices[4].myColor.b = 1.0f;
	tempVertices[4].myColor.a = 1.0f;*/

	tempVertices[4].myUV.x = 0.0f;
	tempVertices[4].myUV.y = 1.0f;


	tempVertices[5].myPosition.x = -0.5f;
	tempVertices[5].myPosition.y = -0.5f;
	tempVertices[5].myPosition.z = 0.5f;
	tempVertices[5].myPosition.a = 1.0f;

	/*tempVertices[5].myColor.r = 1.0f;
	tempVertices[5].myColor.g = 1.0f;
	tempVertices[5].myColor.b = 0.0f;
	tempVertices[5].myColor.a = 1.0f;*/

	tempVertices[5].myUV.x = 1.0f;
	tempVertices[5].myUV.y = 1.0f;


	tempVertices[6].myPosition.x = 0.5f;
	tempVertices[6].myPosition.y = -0.5f;
	tempVertices[6].myPosition.z = 0.5f;
	tempVertices[6].myPosition.a = 1.0f;

	/*tempVertices[6].myColor.r = 0.0f;
	tempVertices[6].myColor.g = 1.0f;
	tempVertices[6].myColor.b = 1.0f;
	tempVertices[6].myColor.a = 1.0f;*/

	tempVertices[6].myUV.x = 0.0f;
	tempVertices[6].myUV.y = 1.0f;


	tempVertices[7].myPosition.x = 0.5f;
	tempVertices[7].myPosition.y = -0.5f;
	tempVertices[7].myPosition.z = -0.5f;
	tempVertices[7].myPosition.a = 1.0f;

	/*tempVertices[7].myColor.r = 1.0f;
	tempVertices[7].myColor.g = 0.0f;
	tempVertices[7].myColor.b = 1.0f;
	tempVertices[7].myColor.a = 1.0f;*/

	tempVertices[7].myUV.x = 1.0f;
	tempVertices[7].myUV.y = 1.0f;

	/*CU::Vector4f tempChangePositionVector(0.f, 0.f, 1.1f, 1.f);*/

	//float tempResize = 0.5f;

	/*tempVertices[0].myPosition *= tempResize;
	tempVertices[1].myPosition *= tempResize;
	tempVertices[2].myPosition *= tempResize;
	tempVertices[3].myPosition *= tempResize;
	tempVertices[4].myPosition *= tempResize;
	tempVertices[5].myPosition *= tempResize;
	tempVertices[6].myPosition *= tempResize;
	tempVertices[7].myPosition *= tempResize;*/




	tempArrayOfIndices[0] = 0;
	tempArrayOfIndices[1] = 1;
	tempArrayOfIndices[2] = 2;
	tempArrayOfIndices[3] = 0;
	tempArrayOfIndices[4] = 2;
	tempArrayOfIndices[5] = 3;

	tempArrayOfIndices[6] = 4;
	tempArrayOfIndices[7] = 6;
	tempArrayOfIndices[8] = 5;
	tempArrayOfIndices[9] = 4;
	tempArrayOfIndices[10] = 7;
	tempArrayOfIndices[11] = 6;

	tempArrayOfIndices[12] = 4;
	tempArrayOfIndices[13] = 5;
	tempArrayOfIndices[14] = 1;
	tempArrayOfIndices[15] = 4;
	tempArrayOfIndices[16] = 1;
	tempArrayOfIndices[17] = 0;

	tempArrayOfIndices[18] = 6;
	tempArrayOfIndices[19] = 7;
	tempArrayOfIndices[20] = 3;
	tempArrayOfIndices[21] = 6;
	tempArrayOfIndices[22] = 3;
	tempArrayOfIndices[23] = 2;

	tempArrayOfIndices[24] = 4;
	tempArrayOfIndices[25] = 0;
	tempArrayOfIndices[26] = 3;
	tempArrayOfIndices[27] = 4;
	tempArrayOfIndices[28] = 3;
	tempArrayOfIndices[29] = 7;

	tempArrayOfIndices[30] = 6;
	tempArrayOfIndices[31] = 2;
	tempArrayOfIndices[32] = 1;
	tempArrayOfIndices[33] = 6;
	tempArrayOfIndices[34] = 1;
	tempArrayOfIndices[35] = 5;

	CDXModel * tempModel = new CDXModel();

	tempModel->Init(tempVertices, tempArrayOfIndices);

	return *tempModel;
}

CDXModel & CHUGModelManager::CreateModel(const std::string & aFilePath)
{
	CDXModel * tempInstance = nullptr;

	if (myInstanceHandler.GetObjectInstance(aFilePath, tempInstance) == true)
	{
		CLoaderModel & tempInputModel = *myModelLoader->LoadModel(aFilePath.c_str());

		DL_ASSERT(&tempInputModel != nullptr, "Model not loaded!");

		tempInstance->Init(tempInputModel);
	}

	return *tempInstance;
}
