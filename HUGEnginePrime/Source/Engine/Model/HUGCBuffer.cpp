#include "stdafx.h"
//#include "HUGCBuffer.h"
//
//
//CHUGCBuffer::CHUGCBuffer()
//{
//}
//
//
//CHUGCBuffer::~CHUGCBuffer()
//{
//}
//
//void CHUGCBuffer::Init()
//{
//	D3D11_BUFFER_DESC tempMatrixBufferDesc;
//
//	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
//	tempMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//	tempMatrixBufferDesc.ByteWidth = sizeof(MatrixBuffer);
//	tempMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	tempMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	tempMatrixBufferDesc.MiscFlags = 0;
//	tempMatrixBufferDesc.StructureByteStride = 0;
//
//	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
//	tempResult = tempDeviceRef.CreateBuffer(&tempMatrixBufferDesc, NULL, &myMatrixBuffer);
//}
//