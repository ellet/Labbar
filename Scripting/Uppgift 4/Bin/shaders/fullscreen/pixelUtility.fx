#include "common.fx"

SamplerState defaultSamplerState;

PixelOutput PShader_Copy(PixelInput aInput)
{
	PixelOutput output;
    output.color = resourceTextureOne.Sample(defaultSamplerState, aInput.uv);
	return output;
}

PixelOutput PShader_Add(PixelInput aInput)
{
    float3 resourceOne = resourceTextureOne.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;
    float3 resourceTwo = resourceTextureTwo.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;

    PixelOutput output;
    output.color = float4(resourceOne.rgb + resourceTwo.rgb, 1.f);
    return output;
}