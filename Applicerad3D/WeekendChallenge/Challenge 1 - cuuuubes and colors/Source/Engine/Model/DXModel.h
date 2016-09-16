#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include "ModelLoader/FBX_Loader_assimp/FBXLoader.h"


class CHUGEffect;
class CLoaderModel;

class CDXModel
{
public:
	struct Vertex
	{
		CU::Vector4f myPosition;
		CU::Vector4f myNormal;
		CU::Vector4f myTangent;
		CU::Vector4f myBiTangent;
		CU::Vector2f myUV;
	};

	CDXModel();
	~CDXModel();

	void Init(const CU::GrowingArray<Vertex> & aArrayOfVertices, const CU::GrowingArray<unsigned int> & aArrayOfIndices);
	void Init(const CLoaderModel & aModelToLoadFrom);

	void Render(const CU::Matrix44f & aModelTransform, const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform);

private:
	void ShapeBufferInit();

	void LoadModel(const CU::GrowingArray<Vertex> & aArrayOfVertices, const CU::GrowingArray<unsigned int> & aArrayOfIndices);

	void InitBuffers(const CLoaderMesh & aModelData);

	void RenderBuffers();
	void RenderModel();
	void ShutdownBuffers();

	CU::GrowingArray<CDXModel*> myChildren;

	CU::GrowingArray<Vertex> myVertices;
	CU::GrowingArray<unsigned int> myIndices;
	unsigned int myIndexCount;

	CHUGEffect * myEffect;
	unsigned int myStrideSize;

	ID3D11Buffer * myVertexBuffer;
	ID3D11Buffer * myIndexBuffer;
};

