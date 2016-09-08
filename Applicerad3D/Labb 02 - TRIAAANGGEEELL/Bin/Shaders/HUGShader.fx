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
	

	/*float4 tempColor;
	tempColor[0] = 1.f;
	tempColor[1] = 0.8f;
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









