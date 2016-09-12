Texture2D ShaderTexture: register(t0);
SamplerState Sampler;

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : UV;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : UV;
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
    
	//Adam told us to set alpha to 1
    tempOutput.color = aInput.color;
	//tempOutput.w = 1.f;
	
	return tempOutput;
}

// pixel shader
PixelOutputType HUGPixelShader(PixelInputType aInput)
{
	PixelOutputType tempOutput;
	tempOutput.color = ShaderTexture.Sample(Sampler, aInput.uv);
	//tempOutput.color[0] = 1.f * aInput.position[0];
	//tempOutput.color[1] = 1.f;
	//tempOutput.color[2] = 1.f;
	//tempOutput.color[3] = 1.f;

	return tempOutput;
}











