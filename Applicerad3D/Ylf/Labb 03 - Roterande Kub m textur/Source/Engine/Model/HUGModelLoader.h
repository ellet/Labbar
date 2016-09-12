#pragma once

class CDXModel;

class CHUGModelLoader
{
public:
	CHUGModelLoader();
	~CHUGModelLoader();

	CDXModel & CreateQuad();
	CDXModel & CreateTriangle();

	CDXModel & CreateCube();

private:

};

