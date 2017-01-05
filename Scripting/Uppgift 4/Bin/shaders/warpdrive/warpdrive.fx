#include "../utility/noiseSimplex.fx"

cbuffer WarpDriveCBuffer : register(b1)
{
	float2 resolution;
	float timer;
	float junk;
};

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

float3 ToLinear(float3 aColor)
{
	return pow(aColor, 2.2);
}

float3 SampleRandom(float2 uv)
{
	float2 zoom = float2(500.0f, 500.0f / (resolution.x / resolution.y));
	
	return float3(snoise(uv * zoom),
		snoise(uv * float2(1.0f, -1.0f) * zoom),
		snoise(-uv * zoom));
} 

float3 ToGamma(float3 aColor)
{
	return pow(aColor, 1.0 / 2.2);
}

float3 Noise(int2 x)
{
	return SampleRandom(float2(x));
}

float3 Random(int x)
{
	return SampleRandom(float2(x, x));
}

float avg(float3 v)
{
	return (v.x + v.y + v.z) / 3.0f;
}

Texture2D boundTexture : register(t0);
SamplerState samplerState;

float4 DoStuff(PixelInputType input, float myAlpha)
{
	float3 ray;
	ray.xy = 2.0f * (input.position.xy - resolution.xy * 0.5f) / resolution.x;
	ray.z = 1.0f;
	
	float mySpeed = 0.7f;
    float myStarLength = 4.0f;
    
	float offset = timer * mySpeed;	
	float speed2 = myStarLength;
	float speed = speed2 + 0.4f;
	offset += offset * 0.96f;
	offset *= 2.0f;
	
	
	float3 col = float3(0.0f, 0.0f, 0.0f);
	
	float3 stp = ray / max(abs(ray.x), abs(ray.y));
	
	float3 pos = 2.0*stp+.5;
	for ( int i=0; i < 15; i++ )
	{
		float z = Noise(float2(pos.xy)).x;
		z = frac(z-offset);
		float d = 50.0*z-pos.z;
		float w = pow(max(0.0f, 1.0f - 8.0f * length(frac(pos.xy) - 0.5f)), 2.0f);
		
		float red = 1.0f - abs(d + speed2 * 0.5f) / speed;
		float blue = 1.0f - abs(d) / speed;
		float green = 1.0f - abs(d - speed2 * 0.5f) / speed;
		
		float3 c = max(float3(0.f, 0.f, 0.f), float3(red, blue, green));
		col += 1.5f * (1.0f - z) * c * w;
		pos += stp;
	}
	
	return float4(ToGamma(col), avg(ToGamma(col)) * myAlpha);
}

PixelOutputType PShaderExiting(PixelInputType input)
{
    PixelOutputType output;
    output.color.rgba = DoStuff(input, max(0.0f, min(1.0f, (timer - 1.0f) * 4.f)));
    return output;
}

PixelOutputType PShaderEntering(PixelInputType input)
{
    PixelOutputType output;
    output.color.rgba = DoStuff(input, 1.f - max(0.f, timer - 2.0f) * 2.f);
    return output;
}

