struct VertexInputType
{
	float4 position : POSITION;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
};

struct PixelOutputType
{
	float4 position : SV_TARGET;
	//float4 Color 
};

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

// pixel shader?
PixelOutputType HUGPixelShader(PixelInputType aInput)
{
	PixelOutputType tempOutput = aInput;
	tempOutput.position[0] = 1.f;
	tempOutput.position[1] = 0.55f;
	tempOutput.position[2] = 0.f;
	tempOutput.position[3] = 1.f;

	/*float4 tempColor;
	tempColor[0] = 1.f;
	tempColor[1] = 0.4f;
	tempColor[2] = 0.f;
	tempColor[3] = 1.f;*/

	return tempOutput;
}


// vertexshader?
PixelInputType HUGVertexShader(VertexInputType aInput)
{
	PixelInputType tempOutput = aInput;
	return tempOutput;
}









