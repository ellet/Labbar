#pragma once
#include "VertexStructs.h"
#include <map>

using namespace FBXLoader;
struct BoneInfo
{
	Matrix44f BoneOffset;
	Matrix44f FinalTransformation;

	BoneInfo()
	{

	}
};

// One model can contain multiple meshes
class CLoaderMesh
{
public:
	CLoaderMesh() 
	{
		myShaderType = 0; 
		myVerticies = nullptr; 
		myVertexBufferSize = 0; 
		myVertexCount = 0; 
		myModel = nullptr; 

		myIndexes.Init(2);
		myChildren.Init(2);
	}

	~CLoaderMesh()
	{}

	CU::GrowingArray<unsigned int> myIndexes;
	CU::GrowingArray<CLoaderMesh*> myChildren;
	unsigned int myShaderType;
	unsigned int myVertexBufferSize;
	int myVertexCount;
	class CLoaderModel* myModel;
	char* myVerticies;
};

class CLoaderModel
{
public:
	CLoaderModel()
	{ 
		myIsLoaded = false; 
		myAnimationDuration = 0.0f; 

		myMeshes.Init(2);
		myTextures.Init(2);
		myBoneInfo.Init(2);
	}

	~CLoaderModel()
	{}

	void SetData(const char* aModelPath)
	{
		myModelPath = aModelPath; 
	}

	CLoaderMesh* CreateMesh()
	{
		CLoaderMesh *model = new CLoaderMesh();
		myMeshes.Add(model); 
		model->myModel = this; return model; 
	}

	CU::GrowingArray<CLoaderMesh*> myMeshes;
	std::string myModelPath;
	float myAnimationDuration;
	const struct aiScene* myScene;
	Matrix44f myGlobalInverseTransform;
	bool myIsLoaded;
	CU::GrowingArray<std::string> myTextures;
	// Animation data
	CU::GrowingArray<BoneInfo> myBoneInfo;
	std::map<std::string, unsigned int> myBoneNameToIndex;
	unsigned int myNumBones;


};


class CFBXLoader
{
public:
	CFBXLoader();
	~CFBXLoader();
	CLoaderModel *LoadModel(const char* aModel);

private:
	void* LoadModelInternal(CLoaderModel* someInput);
	int DetermineAndLoadVerticies(struct aiMesh* aMesh, CLoaderMesh* aLoaderMesh);
	void LoadMaterials(const struct aiScene *sc, CLoaderModel* aModel);
	void LoadTexture(int aType, CU::GrowingArray<std::string>& someTextures, struct aiMaterial* aMaterial);

};

