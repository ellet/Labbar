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
	void InitAsCube(const CU::Vector3f & aPosition = CU::Vector3f::Zero, const CU::Vector3f & aScale = CU::Vector3f::Zero);
	void Init(const std::string & aModelFilePath, const std::wstring & aTextureFilepath = L"Sprites/adam.dds");

	void Render(const CHUGCameraInterface & aCamera);

	void Rotate();
	void SetPosition(const CU::Vector3f & aPosition = CU::Vector3f::Zero);

private:
	void InitEffectAndTexture(const std::wstring & aTextureFilepath = L"Sprites/adam.dds");

	CDXModel * myModel;
	CHUGTexture * myTexture;
	CU::Matrix44f myTransformation;
};