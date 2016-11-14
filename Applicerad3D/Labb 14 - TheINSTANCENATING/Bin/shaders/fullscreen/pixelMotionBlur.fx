#include "common.fx"

SamplerState defaultSamplerState;



PixelOutput PShader_MotionBlur(PixelInput aInput)
{
    PixelOutput output;

    float numberOfSamples = 10.0f;
    float blurSize = 10.0f;

    float2 resourceTwo = resourceTextureOne.SampleLevel(defaultSamplerState, aInput.uv, 0).rg;
    resourceTwo *= blurSize;
    resourceTwo /= numberOfSamples;

    float2 textureSample = aInput.uv;
    float3 finalColor = float3(0.f, 0.f, 0.f);

    for (int indexBlur = 0; indexBlur < numberOfSamples; indexBlur++)
    {
        float3 currentColor = resourceTextureTwo.SampleLevel(defaultSamplerState, textureSample, 0).rgb;
        finalColor += currentColor;
        textureSample += resourceTwo;
    }

    finalColor /= numberOfSamples;

    output.color = float4(finalColor, 1.f);
    return output;

}