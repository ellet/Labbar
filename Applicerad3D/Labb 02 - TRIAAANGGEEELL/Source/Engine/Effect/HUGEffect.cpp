#include "stdafx.h"
#include "HUGEffect.h"
#include "Engine\HUGEngine.h"
#include "HUGFramework\HUGDXFramework.h"
#include "HUGEffectHelper.h"


CHUGEffect::CHUGEffect()
{
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

	HUGEffectHelper::CreateLayout(tempPolyLayout, "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

	tempResult = tempDeviceRef.CreateInputLayout(&tempPolyLayout[0], tempPolyLayout.Size(), tempVertexShaderBuffer->GetBufferPointer(), tempVertexShaderBuffer->GetBufferSize(), &myLayout);
	DL_ASSERT(tempResult == S_OK, "Failed to create input layout");

	tempVertexShaderBuffer->Release();
	tempVertexShaderBuffer = nullptr;

	tempPixelShaderBuffer->Release();
	tempPixelShaderBuffer = nullptr;
}

void CHUGEffect::Active()
{
	//TODO:: activate stuff
}

void CHUGEffect::Render()
{
	HRESULT tempResult = S_OK;

	// Set the shader parameters that it will use for rendering.
	/*tempResult = SetShaderParameters();
	
	DL_ASSERT(tempResult == S_OK, "Set shade parameters failed");*/

	// Now render the prepared buffers with the shader.
	RenderShader();
}



void CHUGEffect::RenderShader()
{
	ID3D11DeviceContext & tempDeviceContextRef = CHUGEngineSingleton::GetFramework().GetDeviceContext();

	UINT myVertexCount = 3;

	// Set the vertex input layout.
	tempDeviceContextRef.IASetInputLayout(myLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	tempDeviceContextRef.VSSetShader(myVertexShader, NULL, 0);
	tempDeviceContextRef.PSSetShader(myPixelShader, NULL, 0);

	// Render the triangle.
	tempDeviceContextRef.Draw(myVertexCount, 0);

	return;
}
