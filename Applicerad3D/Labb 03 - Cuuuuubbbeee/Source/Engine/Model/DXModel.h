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
	void Render(const CU::Matrix44f & aModelTransform, const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform);

	void LoadModel(const CU::GrowingArray<Vertex> & aArrayOfVertices, const CU::GrowingArray<unsigned int> & aArrayOfIndices);

private:
	void InitBuffers();
	void InitVertices();
	void InitIndices();

	void RenderBuffers();
	void RenderModel();
	void ShutdownBuffers();

	CU::GrowingArray<Vertex> myVertices;
	CU::GrowingArray<unsigned int> myIndices;

	CHUGEffect * myEffect;

	ID3D11Buffer * myVertexBuffer;
	ID3D11Buffer * myIndexBuffer;
};

