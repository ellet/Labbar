#include "stdafx.h"
#include "HUGCBuffer.h"
#include "Engine\HUGEngine.h"
#include "HUGFramework\HUGDXFramework.h"


CHUGCBuffer::CHUGCBuffer()
{
	myCurrentIndex = 0;
	myDataSize = 0;
	myDataPtr = nullptr;
	myBuffer = nullptr;
}


CHUGCBuffer::~CHUGCBuffer()
{
	if (myDataPtr != nullptr)
	{
		SAFE_DELETE(myDataPtr);
	}

	if (myBuffer != nullptr)
	{
		myBuffer->Release();
		myBuffer = nullptr;
	}
}

void CHUGCBuffer::Init(const int aSizeOfBuffer)
{
	myDataPtr = new char[aSizeOfBuffer];
	myDataSize = aSizeOfBuffer;

	HRESULT tempResult = S_OK;

	D3D11_BUFFER_DESC tempMatrixBufferDesc;

	ID3D11Device & tempDeviceRef = CHUGEngineSingleton::GetFramework().GetDevice();

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	tempMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tempMatrixBufferDesc.ByteWidth = aSizeOfBuffer;
	tempMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tempMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tempMatrixBufferDesc.MiscFlags = 0;
	tempMatrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	tempResult = tempDeviceRef.CreateBuffer(&tempMatrixBufferDesc, NULL, &myBuffer);

	DL_ASSERT(tempResult == S_OK, "Buffer could not be created");
}

void CHUGCBuffer::Activate()
{
	HRESULT tempResult = S_OK;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	char * tempDataPtr;


	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();

	tempResult = tempDeviceContextRef.Map(myBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	DL_ASSERT(tempResult == S_OK, "Failed to map matrixbuffer");

	// Get a pointer to the data in the constant buffer.
	DL_ASSERT(myCurrentIndex == myDataSize, "constant buffer has not recieved all datat needed");

	memcpy(mappedResource.pData, myDataPtr, myDataSize);
	
	tempDeviceContextRef.VSSetConstantBuffers(0, 1, &myBuffer);

	// Unlock the constant buffer.
	tempDeviceContextRef.Unmap(myBuffer, 0);

	myCurrentIndex = 0;
}