#include "common.fx"

float4 PShader(PixelInput aInput) : SV_TARGET0
{
	float4 albedo = boundTexture.Sample(samplerState, aInput.uv);
	albedo = albedo * aInput.instanceColor;
	
	float4 output;
    output = albedo;
	return output;
}
