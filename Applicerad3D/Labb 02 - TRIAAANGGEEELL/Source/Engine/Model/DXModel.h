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
	};

	CDXModel();
	~CDXModel();

	void Init();
	void Render();

private:
	void InitBuffers();
	void InitVertices();

	void RenderBuffers();
	void RenderModel();
	void ShutdownBuffers();

	CU::GrowingArray<Vertex>myVertices;

	CHUGEffect * myEffect;

	ID3D11Buffer * myVertexBuffer;
	ID3D11Buffer * myIndexBuffer;

	//int myIndexCount; //QUE^^ size of vertices?
};

