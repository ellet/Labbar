#pragma once

class CDXModel;
class CHUGTexture;
class CHUGCameraInterface;

class CHUGModel
{
public:
	CHUGModel();
	~CHUGModel();

	void InitAsTriangle();
	void InitAsQuad();
	void InitAsCube();

	void Init();
	void Render(const CHUGCameraInterface & aCamera);

	void Rotate();

private:
	CDXModel * myModel;
	CHUGTexture * myTexture;
	CU::Matrix44f myTransformation;
};