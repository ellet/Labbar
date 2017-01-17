#include "common.fx"
#include "lys.fx"

PixelOutput PShader(PixelInput aInput)
{
	PixelOutput output;
    output.color = aInput.instanceColor;
	output.color.a = 1.0f;
	return output;
}
