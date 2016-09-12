struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

// pixel shader?
PixelOutputType HUGPixelShader(PixelInputType aInput)
{
	PixelOutputType tempOutput;
	tempOutput.color = aInput.color;

	return tempOutput;
}


// vertexshader?
PixelInputType HUGVertexShader(VertexInputType aInput)
{
	PixelInputType tempOutput = aInput;
	return tempOutput;
}









