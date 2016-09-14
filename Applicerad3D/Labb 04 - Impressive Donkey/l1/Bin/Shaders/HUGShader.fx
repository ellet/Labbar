/////////////
// GLOBALS //
/////////////
Texture2D ShaderTexture;
SamplerState Sampler;


struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 UV : UV0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 UV : UV0;
};

cbuffer MatriserBuffer : register(b0)
{
	float4x4 WorldMatris;
	float4x4 CameraMatris;
	float4x4 ProjectionMatris;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////


// vertexshader
PixelInputType HUGVertexShader(VertexInputType aInput)
{
	PixelInputType tempOutput;
	tempOutput.UV = aInput.UV;

	// Change the position vector to be 4 units for proper matrix calculations.
	aInput.position.w = 1.f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	tempOutput.position = mul(aInput.position, WorldMatris);
	tempOutput.position = mul(tempOutput.position, CameraMatris);
	tempOutput.position = mul(tempOutput.position, ProjectionMatris);

	// Store the input color for the pixel shader to use.
	tempOutput.color = aInput.color;

	return tempOutput;
}

// pixel shader
PixelOutputType HUGPixelShader(PixelInputType aInput)
{
	PixelOutputType tempOutput;
	tempOutput.color = ShaderTexture.Sample(Sampler, aInput.UV);

	return tempOutput;
}









