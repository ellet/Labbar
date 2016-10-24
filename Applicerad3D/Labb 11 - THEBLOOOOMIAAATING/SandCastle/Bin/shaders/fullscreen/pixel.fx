#include "common.fx"

PixelOutput PShader(PixelInput aInput)
{
    float3 SampledColor = boundTexture.Sample(samplerState, aInput.uv).rgb;

    PixelOutput tempOutput;
    tempOutput.color = float4(SampledColor.rgb, 1.f);

	return tempOutput;
}
