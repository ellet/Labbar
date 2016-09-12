#pragma once
#include <d3d11.h>
#include <directxmath.h>

class CHUGEffect;

class CDXModel
{
public:
	struct Vertex
	{
		CU::Vector4f myPosition;
		CU::Vector4f myColor;
		CU::Vector2f myUV;
	};

	CDXModel();
	~CDXModel();

	void Init();
	void Render(const CU::Matrix44f & aToWorld, const CU::Matrix44f & aToCamera, const CU::Matrix44f & aToProjection, ID3D11ShaderResourceView* aTexture);

	void SetVertices(const CU::GrowingArray<Vertex> & someVertices);
	void SetIndexes(const CU::GrowingArray<unsigned int> & someIndexes);

private:
	void InitBuffers();
	void InitVertices();
	void InitIndices();

	void RenderBuffers();
	void RenderModel();
	void ShutdownBuffers();

	CU::GrowingArray<Vertex> myVertices;
	CU::GrowingArray<unsigned int> myIndexes;

	CHUGEffect * myEffect;

	ID3D11Buffer * myVertexBuffer;
	ID3D11Buffer * myIndexBuffer;
};

