#include "common.fx"
#include "lys.fx"

PixelOutput PShader(PixelInput aInput)
{
	PixelOutput output;
    output.color.xyz = float3(0.0f, 0.0f, 0.0f);
	output.color.a = 1.0f;
	return output;
}
