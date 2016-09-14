#include "stdafx.h"
#include "DXModel.h"
#include "Effect/HUGEffect.h"
#include "Engine/HUGEngine.h"
#include "HUGFramework/HUGDXFramework.h"



CDXModel::CDXModel()
{
	myEffect = new CHUGEffect();
	myVertices.Init(4);
	myVertices.Resize(4);
}

CDXModel::~CDXModel()
{
	ShutdownBuffers();
	SAFE_DELETE(myEffect);
}

void CDXModel::Init()
{
	InitBuffers();
	myEffect->Init();
}

void CDXModel::Render(const CU::Matrix44f & aModelTransform, const CU::Matrix44f & aCameraTransform, const CU::Matrix44f & aProjectionTransform)
{

	MatrixBuffer tempMatrixes;
	tempMatrixes.myCamera = aCameraTransform;
	tempMatrixes.myWorld = aModelTransform;
	tempMatrixes.myProjection = aProjectionTransform;

	RenderBuffers();
	myEffect->ActivateEffect(tempMatrixes);
	RenderModel();
}

void CDXModel::LoadModel(const CU::GrowingArray<Vertex> & aArrayOfVertices, const CU::GrowingArray<unsigned int> & aArrayOfIndices)
{
	myVertices = aArrayOfVertices;
	myIndices = aArrayOfIndices;
}

void CDXModel::InitBuffers()
{
	HRESULT tempResult = S_OK;

	ID3D11Device & tempDeviceRef = CHUGEngineSingleton::GetFramework().GetDevice();

	D3D11_BUFFER_DESC tempVertexBufferDesc;
	D3D11_BUFFER_DESC tempIndexBufferDesc;
	D3D11_SUBRESOURCE_DATA tempVertexData;
	D3D11_SUBRESOURCE_DATA tempIndexData;

	// Set up the description of the static vertex buffer.
	tempVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tempVertexBufferDesc.ByteWidth = sizeof(Vertex) * myVertices.Size();
	tempVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tempVertexBufferDesc.CPUAccessFlags = 0;
	tempVertexBufferDesc.MiscFlags = 0;
	tempVertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	tempVertexData.pSysMem = &myVertices[0];
	tempVertexData.SysMemPitch = 0;
	tempVertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	tempResult = tempDeviceRef.CreateBuffer(&tempVertexBufferDesc, &tempVertexData, &myVertexBuffer);
	
	DL_ASSERT(tempResult == S_OK, "Vertex buffer creation failed");

	// Set up the description of the static index buffer.
	tempIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tempIndexBufferDesc.ByteWidth = sizeof(unsigned long) * myIndices.Size();
	tempIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tempIndexBufferDesc.CPUAccessFlags = 0;
	tempIndexBufferDesc.MiscFlags = 0;
	tempIndexBufferDesc.StructureByteStride = 0;

	tempIndexData.pSysMem = &myIndices[0];
	tempIndexData.SysMemPitch = 0;
	tempIndexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	tempResult = tempDeviceRef.CreateBuffer(&tempIndexBufferDesc, &tempIndexData, &myIndexBuffer);
	DL_ASSERT(tempResult == S_OK, "Indexbuffer creation failed");

}

void CDXModel::RenderBuffers()
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex);
	offset = 0;

	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	tempDeviceContextRef.IASetVertexBuffers(0, 1, &myVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	tempDeviceContextRef.IASetIndexBuffer(myIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	tempDeviceContextRef.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void CDXModel::RenderModel()
{
	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();
	
	// Render the model.
	tempDeviceContextRef.DrawIndexed(myIndices.Size(), 0, 0);
}

void CDXModel::ShutdownBuffers()
{
	// Release the index buffer.
	if (myIndexBuffer != nullptr)
	{
		myIndexBuffer->Release();
		myIndexBuffer = nullptr;
	}

	// Release the vertex buffer.
	if (myVertexBuffer != nullptr)
	{
		myVertexBuffer->Release();
		myVertexBuffer = nullptr;
	}

	return;
}