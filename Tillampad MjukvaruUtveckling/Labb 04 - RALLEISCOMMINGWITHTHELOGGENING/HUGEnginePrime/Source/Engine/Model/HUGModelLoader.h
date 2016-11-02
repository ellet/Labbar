#pragma once

class CDXModel;
class CFBXLoader;

class CHUGModelLoader
{
public:
	CHUGModelLoader();
	~CHUGModelLoader();

	CDXModel & CreateQuad();
	CDXModel & CreateTriangle();
	CDXModel & CreateCube();

	CDXModel & CreateQuadTopLeft();

	CDXModel & CreateModel(const std::string & aFilePath);

private:
	CFBXLoader * myModelLoader;
};