#include "common.fx"

SamplerState defaultSamplerState;

cbuffer MotioBlurConstantBuffer : register(b4)
{
	float blurMultiplier;
	float3 padding;
}

PixelOutput PShader_MotionBlur(PixelInput aInput)
{
    PixelOutput output;

    const float numberOfSamples = 10.0f;
	const float blurStrength = 10.0f * blurMultiplier;
	
    float2 blur = resourceTextureOne.SampleLevel(defaultSamplerState, aInput.uv, 0).rg;
	blur *= blurStrength;
	blur /= numberOfSamples;

    float2 textureSample = aInput.uv;
    float3 finalColor = float3(0.f, 0.f, 0.f);
    for (int indexBlur = 0; indexBlur < numberOfSamples; indexBlur++)
    {
        float3 currentColor = resourceTextureTwo.SampleLevel(defaultSamplerState, textureSample, 0).rgb / numberOfSamples;
        finalColor += currentColor;
        textureSample += blur;
    }

    output.color = float4(finalColor, 1.f);
    return output;

}