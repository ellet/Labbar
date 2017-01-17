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

#define NUM_SAMPLES 16

cbuffer LightConstantBuffer : register(b4)
{
	float2 lightPos;
	float density;
	float decay;
	float weight;
	float exposure;
	float2 padding;
}

Texture2D boundTexture : register( t0 );
SamplerState samplerState;

PixelOutputType PShader(PixelInputType input)
{
	float2 texc = input.uv;
    
    float2 dTexC = (texc - lightPos);
    dTexC *= (1.0f / float(NUM_SAMPLES) * density);
    float4 col = boundTexture.Sample(samplerState, texc);
    float illuminationDecay = 1.0f;
    float4 sample;
    
    for (int i=0; i<NUM_SAMPLES; i++)
    {
        texc -= dTexC;
        sample = boundTexture.Sample(samplerState, texc);
        sample *= illuminationDecay * weight;
        col += sample;
        illuminationDecay *= decay;
    }
	
	PixelOutputType output;
	output.color = col;
	return output;
}
