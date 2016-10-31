#include "common.fx"

PixelInput VShader(VertexInput input)
{
	PixelInput output;

    output.position = input.position;
    output.uv = input.uv;

	return output;
}
