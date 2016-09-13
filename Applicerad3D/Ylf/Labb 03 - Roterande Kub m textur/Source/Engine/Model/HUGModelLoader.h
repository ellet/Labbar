#pragma once

class CDXModel;

class CHUGModelLoader
{
public:
	CHUGModelLoader();
	~CHUGModelLoader();

	CDXModel & CreateQuad();
	CDXModel & CreateTriangle();

	CDXModel & CreateCube(const CU::Vector3f & aScale = CU::Vector3f::One);

private:

};

