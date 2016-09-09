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
	};

	CDXModel();
	~CDXModel();

	void Init();
	void Render();

	void SetVertices(const CU::GrowingArray<Vertex> & someVertices);

private:
	void InitBuffers();
	void InitVertices();
	void InitIndices();

	void RenderBuffers();
	void RenderModel();
	void ShutdownBuffers();

	CU::GrowingArray<Vertex> myVertices;
	CU::GrowingArray<unsigned int> myIndexCount;

	CHUGEffect * myEffect;

	ID3D11Buffer * myVertexBuffer;
	ID3D11Buffer * myIndexBuffer;
};

