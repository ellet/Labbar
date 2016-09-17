/////////////
// GLOBALS //
/////////////
Texture2D ShaderTexture;
SamplerState Sampler;
float ElapsedTime;


struct VertexInputType
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
	float2 UV : UV0;
	//float4 color : COLOR;
	
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 UV : UV0;
	//float4 color : COLOR;
	
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
// Extra Functions
////////////////////////////////////////////////////////////////////////////////

PixelInputType CreateDefaultPixelInput(float4 aPosition)
{
	PixelInputType tempOutput;
	
	tempOutput.position = aPosition;
	tempOutput.UV.x = 0; tempOutput.UV.y = 0;
	
	return tempOutput;
}


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
	//tempOutput.color = aInput.color;

	return tempOutput;
}

// pixel shader
PixelOutputType HUGPixelShader(PixelInputType aInput)
{
	PixelOutputType tempOutput;
	float4 tempColor;
	tempColor.r = aInput.UV.x;
	tempColor.g = aInput.UV.y;
	tempColor.b = aInput.UV.x;
	tempColor.a = 1.0;
	
	tempOutput.color = tempColor;//ShaderTexture.Sample(Sampler, aInput.UV);

	return tempOutput;
}










