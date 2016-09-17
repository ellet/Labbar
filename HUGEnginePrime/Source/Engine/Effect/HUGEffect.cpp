#include "stdafx.h"
#include "HUGEffect.h"
#include "Engine\HUGEngine.h"
#include "HUGFramework\HUGDXFramework.h"
#include "DXHelpers\HUGEffectHelper.h"
#include "DDSLoader\dds.h"
#include "DDSLoader\DDSTextureLoader.h"
#include "DXHelpers\DataTypeEnumConverter.h"


CHUGEffect::CHUGEffect()
{
}


CHUGEffect::~CHUGEffect()
{
}

void CHUGEffect::Init(const std::wstring & aTextureFilePath)
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

	// Create the vertex shader from the buffe.r
	tempResult = tempDeviceRef.CreateVertexShader(tempVertexShaderBuffer->GetBufferPointer(), tempVertexShaderBuffer->GetBufferSize(), NULL, &myVertexShader);
	DL_ASSERT(tempResult == S_OK, "failed to create vertex shader");

	// Create the pixel shader from the buffer.
	tempResult = tempDeviceRef.CreatePixelShader(tempPixelShaderBuffer->GetBufferPointer(), tempPixelShaderBuffer->GetBufferSize(), NULL, &myPixelShader);
	DL_ASSERT(tempResult == S_OK, "failed to create Pixel shader");

	CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC> tempPolyLayout;
	tempPolyLayout.Init(1);

	HUGEffectHelper::CreateLayout(tempPolyLayout, "POSITION", 0, ConvertToDXGI(eDataType::Float4), 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "NORMAL", 0, ConvertToDXGI(eDataType::Float4), 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "TANGENT", 0, ConvertToDXGI(eDataType::Float4), 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "BITANGENT", 0, ConvertToDXGI(eDataType::Float4), 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	HUGEffectHelper::CreateLayout(tempPolyLayout, "UV", 0, ConvertToDXGI(eDataType::Float2), 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	
	//HUGEffectHelper::CreateLayout(tempPolyLayout, "COLOR", 0, ConvertToDXGI(eDataType::Float4), 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	

	tempResult = tempDeviceRef.CreateInputLayout(&tempPolyLayout[0], tempPolyLayout.Size(), tempVertexShaderBuffer->GetBufferPointer(), tempVertexShaderBuffer->GetBufferSize(), &myLayout);
	DL_ASSERT(tempResult == S_OK, "Failed to create input layout");

	tempVertexShaderBuffer->Release();
	tempVertexShaderBuffer = nullptr;

	tempPixelShaderBuffer->Release();
	tempPixelShaderBuffer = nullptr;

	
	DL_ASSERT(tempResult == S_OK, "failed to create matrix buffer");

	tempResult = DirectX::CreateDDSTextureFromFile(&tempDeviceRef, aTextureFilePath.c_str(), nullptr, &myTexture);
	DL_ASSERT(tempResult == S_OK, "Texture was loaded incorrecly");

	D3D11_SAMPLER_DESC tempSamplerDesc;

	// Create a texture sampler state description.
	tempSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	tempSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tempSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tempSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tempSamplerDesc.MipLODBias = 0.0f;
	tempSamplerDesc.MaxAnisotropy = 1;
	tempSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	tempSamplerDesc.BorderColor[0] = 0;
	tempSamplerDesc.BorderColor[1] = 0;
	tempSamplerDesc.BorderColor[2] = 0;
	tempSamplerDesc.BorderColor[3] = 0;
	tempSamplerDesc.MinLOD = 0;
	tempSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


	// Create the texture sampler state.
	tempResult = tempDeviceRef.CreateSamplerState(&tempSamplerDesc, &mySampleState);
	DL_ASSERT(tempResult == S_OK, "failed to set sampler state");
}

void CHUGEffect::ActivateEffect(const MatrixBuffer & aMatrixBuffer)
{

	SetMatrixes(aMatrixBuffer);

	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();


	// Set the vertex input layout.
	tempDeviceContextRef.IASetInputLayout(myLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	tempDeviceContextRef.VSSetShader(myVertexShader, NULL, 0);
	tempDeviceContextRef.PSSetShader(myPixelShader, NULL, 0);

	return;
}

void CHUGEffect::SetMatrixes(const MatrixBuffer & aMatrixBuffer)
{
	HRESULT tempResult = S_OK;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBuffer* dataPtr;
	unsigned int bufferNumber;

	CU::Matrix44f tempWorld = CU::Matrix44f::Transpose(aMatrixBuffer.myWorld);
	CU::Matrix44f tempCamera = CU::Matrix44f::Transpose(aMatrixBuffer.myCamera);
	CU::Matrix44f tempProjection = CU::Matrix44f::Transpose(aMatrixBuffer.myProjection);


	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();

	// Transpose the matrices to prepare them for the shader.

	// Lock the constant buffer so it can be written to.
	tempResult = tempDeviceContextRef.Map(/*Get from cbuffer*/, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	
	DL_ASSERT(tempResult == S_OK, "Failed to map matrixbuffer");

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBuffer*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->myWorld = tempWorld;
	dataPtr->myCamera = tempCamera;
	dataPtr->myProjection = tempProjection;

	// Unlock the constant buffer.
	tempDeviceContextRef.Unmap(/*get from c buffer*/, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	tempDeviceContextRef.VSSetConstantBuffers(bufferNumber, 1, &/*get from c buffer*/);

	// Set shader texture resource in the pixel shader.
	tempDeviceContextRef.PSSetShaderResources(0, 1, &myTexture);
	//tempDeviceContextRef.PSSetSamplers(0, 1, &mySampleState);
}
