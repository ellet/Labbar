Texture2D ShaderTexture: register(t0);
SamplerState Sampler;

struct VertexInputType
{
	float4 position : POSITION;
	float4 normals : NORMALS;
	float4 tangents : TANGENTS;
	float4 bitangents : BITANGENTS;
	float2 uv : UV;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 normals : TEXCOORD1;
	float4 tangents : TEXCOORD2;
	float4 bitangents : TEXCOORD3;
	float2 uv : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};

cbuffer MatrixesBuffer: register(b0)
{
	float4x4 worldMatrix;
	float4x4 cameraMatrix;
	float4x4 projectionMatrix;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

// vertexshader
PixelInputType HUGVertexShader(VertexInputType aInput)
{
	PixelInputType tempOutput = aInput;	

    // Calculate the position of the vertex against the world, view, and projection matrices.
    tempOutput.position = mul(aInput.position, worldMatrix);
    tempOutput.position = mul(tempOutput.position, cameraMatrix);
    tempOutput.position = mul(tempOutput.position, projectionMatrix);
	
	return tempOutput;
}

// pixel shader
PixelOutputType HUGPixelShader(PixelInputType aInput)
{
	PixelOutputType tempOutput;
	tempOutput.color = ShaderTexture.Sample(Sampler, aInput.uv);

	return tempOutput;
}











