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
	void Render();

private:
	CU::Matrix44f myTransformation;
	
	CDXModel * myModel;
};