#include "common.fx"

SamplerState defaultSamplerState;



PixelOutput PShader_Tonemap(PixelInput aInput)
{
    PixelOutput output;
    float3 resource = resourceTextureTwo.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;
    float3 midLuminance = resourceTextureOne.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;

    float3 relativeLuminance = (float3) 0;
	relativeLuminance.r = 0.2126f;
	relativeLuminance.g = 0.7152f;
	relativeLuminance.b = 0.0722f;
    float LuminancePixel = resource.r * relativeLuminance.r + resource.g * relativeLuminance.g + resource.b * relativeLuminance.b;
    float AverageLuminance = midLuminance.r * relativeLuminance.r + midLuminance.g * relativeLuminance.g + midLuminance.b * relativeLuminance.b;
    float3 result = (float3)0;
    float Exposure = 12.0f;

    float Lp = LuminancePixel * Exposure / AverageLuminance;

    result = resource* (Lp / (1 + Lp));

    output.color = float4(result.rgb, 1.f);
    return output;

}