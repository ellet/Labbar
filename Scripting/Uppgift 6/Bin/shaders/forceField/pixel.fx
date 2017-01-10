#include "common.fx"

PixelOutput PShader(PixelInput aInput)
{

    const float4 baseColor = aInput.instanceColor;
	PixelOutput output;
    //float2 uv = fmod(aInput.uv * float2(10.f * (9.f / 16.f), 10.0f), (1.0f).xx);
    float3 sample1 = boundTexture.SampleLevel(samplerState, aInput.uv, 0);
    float3 hexMap = boundTexture.SampleLevel(samplerState, aInput.uv, 0).xyz;
    


    hexMap.b *= (sin((time / 2.f) + hexMap.g * 5) + 1);
    output.color = baseColor * baseColor.a;
    output.color.xyz = baseColor.rgb * hexMap.b;
    output.color.xyz *= length(sample1.xyz) > 0.2f ? 2.f : 1.f;

	return output;
}
