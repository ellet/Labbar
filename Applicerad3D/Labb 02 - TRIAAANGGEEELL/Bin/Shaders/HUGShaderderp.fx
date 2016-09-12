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
	//tempOutput.color[0] = 1.f * aInput.position[0];
	//tempOutput.color[1] = 1.f;
	//tempOutput.color[2] = 1.f;
	//tempOutput.color[3] = 1.f;

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









