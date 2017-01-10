#include "common.fx"
PixelInput VShader(VertexInput aInput)
{
	PixelInput output;
	output.position = aInput.position;
	output.uv = aInput.uv;
	return output;
}