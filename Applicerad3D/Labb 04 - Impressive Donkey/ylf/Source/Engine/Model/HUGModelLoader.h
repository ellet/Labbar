#pragma once

class CDXModel;
class CFBXLoader;

class CHUGModelLoader
{
public:
	CHUGModelLoader();
	~CHUGModelLoader();

	CDXModel & CreateCube(const CU::Vector3f & aScale = CU::Vector3f::One);

	CDXModel & CreateModel(const std::string & aFilePath, CU::GrowingArray<std::string> & aTextureFilePaths);

private:
	CFBXLoader * myLoader;
};

