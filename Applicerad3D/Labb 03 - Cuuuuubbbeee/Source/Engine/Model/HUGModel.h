#pragma once

class CDXModel;

class CHUGModel
{
public:
	CHUGModel();
	~CHUGModel();

	void InitAsTriangle();
	void InitAsQuad();
	void InitAsCube();

	void Init();
	void Update();
	void Render(const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform);

private:
	CU::Matrix44f myTransformation;
	
	CDXModel * myModel;
};