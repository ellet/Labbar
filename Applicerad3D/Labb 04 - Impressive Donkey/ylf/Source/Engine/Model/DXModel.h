#pragma once
#include <d3d11.h>
#include <directxmath.h>

class CHUGEffect;
class CLoaderModel;
class CLoaderMesh;

class CDXModel
{
public:
	struct Vertex
	{
		CU::Vector4f myPosition;
		CU::Vector2f myUV;
		CU::Vector4f myNormals;
		CU::Vector4f myTangents;
		CU::Vector4f myBitangents;
	};

	CDXModel();
	~CDXModel();

	void Init();
	void InitWithModel(const CLoaderModel & aModel);
	void Render(const CU::Matrix44f & aToWorld, const CU::Matrix44f & aToCamera, const CU::Matrix44f & aToProjection, ID3D11ShaderResourceView* aTexture);

	void SetVertices(const CU::GrowingArray<Vertex> & someVertices);
	void SetIndexes(const CU::GrowingArray<unsigned int> & someIndexes);

private:
	void InitBuffers();
	void InitBuffers(const CLoaderMesh & aMeshData);

	void RenderBuffers();
	void RenderModel();
	void ShutdownBuffers();

	CU::GrowingArray<Vertex> myVertices;
	CU::GrowingArray<unsigned int> myIndexes;

	unsigned int myVertexSize;
	unsigned int myIndexCount;

	CHUGEffect * myEffect;

	ID3D11Buffer * myVertexBuffer;
	ID3D11Buffer * myIndexBuffer;
};

