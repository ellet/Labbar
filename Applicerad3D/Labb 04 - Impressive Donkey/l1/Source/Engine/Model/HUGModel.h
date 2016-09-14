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
	void InitAsModel(const std::string & aModelFilePath);

	void Init();
	void Update(const CU::Time & aDeltaTime);
	void Render(const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform);

private:
	CU::Matrix44f myTransformation;
	
	CDXModel * myModel;
};