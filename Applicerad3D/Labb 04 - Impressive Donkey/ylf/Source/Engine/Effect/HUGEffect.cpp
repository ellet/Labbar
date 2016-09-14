#include "stdafx.h"
#include "HUGEffect.h"
#include "Engine\HUGEngine.h"
#include "HUGFramework\HUGDXFramework.h"
#include "HUGEffectHelper.h"


CHUGEffect::CHUGEffect()
{
	myVertexShader = nullptr;
	myPixelShader = nullptr;
	myLayout = nullptr;
	myMatrixBuffer = nullptr;
	mySampleState = nullptr;
}


CHUGEffect::~CHUGEffect()
{

}

void CHUGEffect::Init()
{
	HRESULT tempResult = S_OK;

	ID3D11Device & tempDeviceRef = CHUGEngineSingleton::GetFramework().GetDevice();	

	std::string tempOutput;

	ID3D10Blob * tempPixelShaderBuffer;
	ID3D10Blob * tempVertexShaderBuffer;

	bool tempLoadBool = true;
	tempLoadBool = HUGEffectHelper::CompileShader(L"Shaders/HUGShader.fx", "HUGVertexShader", "vs_5_0", tempVertexShaderBuffer, tempOutput);
	DL_ASSERT(tempLoadBool == true, "failed to load vertexshader");

	tempLoadBool = HUGEffectHelper::CompileShader(L"Shaders/HUGShader.fx", "HUGPixelShader", "ps_5_0", tempPixelShaderBuffer, tempOutput);
	DL_ASSERT(tempLoadBool == true, "failed to load pixelshader");

	// Create the vertex shader from the buffer.
	tempResult = tempDeviceRef.CreateVertexShader(tempVertexShaderBuffer->GetBufferPointer(), tempVertexShaderBuffer->GetBufferSize(), NULL, &myVertexShader);
	DL_ASSERT(tempResult == S_OK, "failed to create vertex shader");

	// Create the pixel shader from the buffer.
	tempResult = tempDeviceRef.CreatePixelShader(tempPixelShaderBuffer->GetBufferPointer(), tempPixelShaderBuffer->GetBufferSize(), NULL, &myPixelShader);
	DL_ASSERT(tempResult == S_OK, "failed to create Pixel shader");

	CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC> tempPolyLayout;
	tempPolyLayout.Init(1);

	HUGEffectHelper::CreateLayout(tempPolyLayout, "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "NORMALS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "TANGENTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "BITANGENTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

	tempResult = tempDeviceRef.CreateInputLayout(&tempPolyLayout[0], tempPolyLayout.Size(), tempVertexShaderBuffer->GetBufferPointer(), tempVertexShaderBuffer->GetBufferSize(), &myLayout);
	DL_ASSERT(tempResult == S_OK, "Failed to create input layout");

	D3D11_SAMPLER_DESC tempSamplerDescription;
	// Create a texture sampler state description.
	tempSamplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	tempSamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tempSamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tempSamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tempSamplerDescription.MipLODBias = 0.0f;
	tempSamplerDescription.MaxAnisotropy = 1;
	tempSamplerDescription.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	tempSamplerDescription.BorderColor[0] = 0;
	tempSamplerDescription.BorderColor[1] = 0;
	tempSamplerDescription.BorderColor[2] = 0;
	tempSamplerDescription.BorderColor[3] = 0;
	tempSamplerDescription.MinLOD = 0;
	tempSamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	tempResult = tempDeviceRef.CreateSamplerState(&tempSamplerDescription, &mySampleState);
	DL_ASSERT(tempResult == S_OK, "Failed to create sampler state!");

	HUGEffectHelper::CreateCBuffer<MatrixBufferType>(0, myMatrixBuffer, &tempDeviceRef);

	tempVertexShaderBuffer->Release();
	tempVertexShaderBuffer = nullptr;

	tempPixelShaderBuffer->Release();
	tempPixelShaderBuffer = nullptr;
}

void CHUGEffect::Active()
{
	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();

	// Set the vertex input layout.
	tempDeviceContextRef.IASetInputLayout(myLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	tempDeviceContextRef.VSSetShader(myVertexShader, NULL, 0);
	tempDeviceContextRef.PSSetShader(myPixelShader, NULL, 0);

	return;
}

void CHUGEffect::Inactivate()
{
	myVertexShader->Release();
	myPixelShader->Release();
	myLayout->Release();
	myMatrixBuffer->Release();
	mySampleState->Release();

	myVertexShader = nullptr;
	myPixelShader = nullptr;
	myLayout = nullptr;
	myMatrixBuffer = nullptr;
	mySampleState = nullptr;
}

void CHUGEffect::SetShaderResources(const CU::Matrix44f aWorldMatrix, const CU::Matrix44f aCameraMatrix,
	const CU::Matrix44f aProjectionMatrix, ID3D11ShaderResourceView* aTexture)
{
	HRESULT tempResult = S_OK;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* constantBufferData;

	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();

	// Transpose the matrices to prepare them for the shader.
	CU::Matrix44f tempWorldMatrix = CU::Matrix44f::Transpose(aWorldMatrix);
	CU::Matrix44f tempCameraMatrix = CU::Matrix44f::Transpose(aCameraMatrix);
	CU::Matrix44f tempProjectionMatrix = CU::Matrix44f::Transpose(aProjectionMatrix);

	// Lock the constant buffer so it can be written to.
	tempResult = tempDeviceContextRef.Map(myMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	DL_ASSERT(tempResult == S_OK, "Failed to lock constant matrix buffer for writing");

	// Get a pointer to the data in the constant buffer.
	constantBufferData = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	constantBufferData->myToWorld = tempWorldMatrix;
	constantBufferData->myToCamera = tempCameraMatrix;
	constantBufferData->myToProjection = tempProjectionMatrix;

	// Unlock the constant buffer.
	tempDeviceContextRef.Unmap(myMatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	unsigned int bufferNumber = 0;

	// finally set the constant buffer in the vertex shader with the updated values.
	tempDeviceContextRef.VSSetConstantBuffers(bufferNumber, 1, &myMatrixBuffer);

	// Set shader texture resource in the pixel shader.
	tempDeviceContextRef.PSSetShaderResources(0, 1, &aTexture);

}
