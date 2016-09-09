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

void CDXModel::Render()
{
	RenderBuffers();
	myEffect->Active();
	RenderModel();
}

void CDXModel::SetVertices(const CU::GrowingArray<Vertex> & someVertices)
{
	myVertices = someVertices;
}

void CDXModel::InitBuffers()
{
	HRESULT tempResult = S_OK;

	ID3D11Device & tempDeviceRef = CHUGEngineSingleton::GetFramework().GetDevice();

	D3D11_BUFFER_DESC tempVertexBufferDesc;
	D3D11_BUFFER_DESC tempIndexBufferDesc;
	D3D11_SUBRESOURCE_DATA tempVertexData;
	D3D11_SUBRESOURCE_DATA tempIndexData;

	InitVertices();
	InitIndices();

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
	tempIndexBufferDesc.ByteWidth = sizeof(unsigned long) * myVertices.Size();
	tempIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tempIndexBufferDesc.CPUAccessFlags = 0;
	tempIndexBufferDesc.MiscFlags = 0;
	tempIndexBufferDesc.StructureByteStride = 0;

	tempIndexData.pSysMem = &myIndexCount[0];
	tempIndexData.SysMemPitch = 0;
	tempIndexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	tempResult = tempDeviceRef.CreateBuffer(&tempIndexBufferDesc, &tempIndexData, &myIndexBuffer);
	DL_ASSERT(tempResult == S_OK, "Indexbuffer creation failed");

}

void CDXModel::InitVertices()
{
	myVertices[0].myPosition.x = -0.5f;
	myVertices[0].myPosition.y = -0.5f;
	myVertices[0].myPosition.z = 0.5f;
	myVertices[0].myPosition.w = 1.f;

	myVertices[0].myColor.r = 0.0f;
	myVertices[0].myColor.g = 1.0f;
	myVertices[0].myColor.b = 0.0f;
	myVertices[0].myColor.a = 1.f;

	myVertices[1].myPosition.x = -0.5f;
	myVertices[1].myPosition.y = 0.5f;
	myVertices[1].myPosition.z = 0.5f;
	myVertices[1].myPosition.w = 1.f;

	myVertices[1].myColor.r = 1.0f;
	myVertices[1].myColor.g = 0.0f;
	myVertices[1].myColor.b = 0.0f;
	myVertices[1].myColor.a = 1.f;

	myVertices[2].myPosition.x = 0.5f;
	myVertices[2].myPosition.y = -0.5f;
	myVertices[2].myPosition.z = 0.5f;
	myVertices[2].myPosition.w = 1.f;

	myVertices[2].myColor.r = 0.0f;
	myVertices[2].myColor.g = 0.0f;
	myVertices[2].myColor.b = 1.0f;
	myVertices[2].myColor.a = 1.f;

	myVertices[3].myPosition.x = 0.5f;
	myVertices[3].myPosition.y = 0.5f;
	myVertices[3].myPosition.z = 0.5f;
	myVertices[3].myPosition.w = 1.f;

	myVertices[3].myColor.r = 1.0f;
	myVertices[3].myColor.g = 1.0f;
	myVertices[3].myColor.b = 0.0f;
	myVertices[3].myColor.a = 1.f;

}

void CDXModel::InitIndices()
{
	//Todo^^ Edit indices to be correct stuff and not vertex stuff
	myIndexCount.Init(myVertices.Size());
	myIndexCount.Resize(myVertices.Size());

	for (unsigned int i = 0; i < myIndexCount.Size(); ++i)
	{
		myIndexCount[i] = i;
	}
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
	tempDeviceContextRef.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	return;
}

void CDXModel::RenderModel()
{
	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();
	
	// Render the model.
	tempDeviceContextRef.Draw(myVertices.Size(), 0);
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