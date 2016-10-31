#include "common.fx"

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};


Texture2D boundTexture : register( t0 );
SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = mul(input.toWorld, input.position);
	output.color = input.color;
	output.uv = input.textureTopLeft + input.uv * input.textureSize;
    // output.uv = input.uv;

    return output;
}

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	output.color = boundTexture.Sample(samplerState, input.uv) * input.color;

    float3 sample = boundTexture.Sample(samplerState, input.uv).rgb;
    float sigDist = median(sample.r, sample.g, sample.b) - 0.5f;
    float opacity = clamp(sigDist / fwidth(sigDist) + 0.5, 0.0, 1.0);
    const float4 bgColor = float4(0.f, 0.f, 0.f, 0.f);
    const float4 fgColor = float4(0.f, 0.f, 0.f, 1.f);
    output.color = lerp(bgColor, fgColor, opacity);

	return output;
}
