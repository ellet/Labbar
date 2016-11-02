#pragma once

#include "CU/Systems/InstanceHandler/InstanceHandler.h"
#include "Model\DXModel.h"

class CDXModel;
class CFBXLoader;

class CHUGModelManager
{
public:
	CHUGModelManager();
	~CHUGModelManager();

	CDXModel & CreateQuad();
	CDXModel & CreateTriangle();
	CDXModel & CreateCube();

	CDXModel & CreateQuadTopLeft();

	CDXModel & CreateModel(const std::string & aFilePath);

private:
	CFBXLoader * myModelLoader;
	CU::InstanceHandler<CDXModel, std::string> myInstanceHandler;
};