#pragma once

class CDXModel;
class CHUGTexture;
class CHUGCameraInterface;

class CHUGModel
{
public:
	CHUGModel();
	~CHUGModel();

	void InitAsCube(const CU::Vector3f & aPosition = CU::Vector3f::Zero, const CU::Vector3f & aScale = CU::Vector3f::Zero);
	void Init(const std::string & aModelFilePath);

	void Render(const CHUGCameraInterface & aCamera);

	void Rotate();
	void SetPosition(const CU::Vector3f & aPosition = CU::Vector3f::Zero);

private:
	void InitTexture(const std::string & aTextureFilepath = "Sprites/adam.dds");

	CDXModel * myModel;
	CU::GrowingArray<CHUGTexture *> myTextures;
	CU::Matrix44f myTransformation;
};