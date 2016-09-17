#include "stdafx.h"
#include "HUGCBuffer.h"
#include "Engine\HUGEngine.h"
#include "HUGFramework\HUGDXFramework.h"


CHUGCBuffer::CHUGCBuffer()
{
	myCurrentIndex = 0;
	myDataSize = 0;
	myDataPtr = nullptr;
	myMatrixBuffer = nullptr;
}


CHUGCBuffer::~CHUGCBuffer()
{
	if (myDataPtr != nullptr)
	{
		SAFE_DELETE(myDataPtr);
	}

	if (myMatrixBuffer != nullptr)
	{
		myMatrixBuffer->Release();
		myMatrixBuffer = nullptr;
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
	tempMatrixBufferDesc.ByteWidth = sizeof(aSizeOfBuffer);
	tempMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tempMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tempMatrixBufferDesc.MiscFlags = 0;
	tempMatrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	tempResult = tempDeviceRef.CreateBuffer(&tempMatrixBufferDesc, NULL, &myMatrixBuffer);
}

void CHUGCBuffer::Activate()
{

}
