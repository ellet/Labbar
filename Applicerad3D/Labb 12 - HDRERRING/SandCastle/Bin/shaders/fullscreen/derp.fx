#include "common.fx"

SamplerState defaultSamplerState;



PixelOutput PShader_Luminance(PixelInput aInput)
{
	PixelOutput output;

	float bloomCutoff = 0.3f;
	float3 resource = boundTexture.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;

	float3 relativeLuminance = (float3) 0;
	relativeLuminance.r = 0.2126f;
	relativeLuminance.g = 0.7152f;
	relativeLuminance.b = 0.0722f;
	float luminance = resource.r * relativeLuminance.r + resource.g * relativeLuminance.g + resource.b * relativeLuminance.b;
	luminance = saturate(luminance - bloomCutoff);
	float3 resourceLuminance = resource * luminance * (1 / bloomCutoff);

	float luminanceLength = length(resourceLuminance);

	output.color = float4(resourceLuminance.rgb, 1.f);
	return output;


}

static const float texelSize = 1.f / 256.f;
static const uint kernelSize = 21;
//static const float weights[kernelSize] = {0.06136f, 0.24477f, 0.38774f, 0.24477f, 0.06136f};
//static const float weights[kernelSize] = { 0.129001f, 0.142521f, 0.151303f,	0.15435f,	0.151303f,	0.142521f,	0.129001f };

static const float weights[kernelSize] = { 0.011254f, 0.016436f, 0.023066f, 0.031105f, 0.040306f, 0.050187f, 0.060049f, 0.069041f, 0.076276f, 0.080977f, 0.082607f, 0.080977f, 0.076276f, 0.069041f, 0.060049f, 0.050187f, 0.040306f, 0.031105f, 0.023066f, 0.016436f, 0.011254f };

//static const float texelOffset[kernelSize] = { -2.f, -1.f, 0, 1.f, 2.f };
//static const float texelOffset[kernelSize] = { -3.f, -2.f, -1.f, 0, 1.f, 2.f, 3.f };
static const float texelOffset[kernelSize] = { -10.f, -9.f, -8.f, -7.f, -6.f, -5.f, -4.f, -3.f, -2.f, -1.f, 0, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f };

PixelOutput PShader_GaussianBlurHorizontal(PixelInput aInput)
{
	PixelOutput output;
	float3 blurColor = (float3) 0;

	for (uint i = 0; i < kernelSize; ++i)
	{
		float2 textureCoords = aInput.uv;
		textureCoords.x += texelSize * texelOffset[i];
		float3 resource = boundTexture.SampleLevel(defaultSamplerState, textureCoords, 0).rgb;
		blurColor += resource * weights[i];
	}

	output.color = float4(blurColor.rgb, 1.f);

	return output;
}

PixelOutput PShader_GaussianBlurVertical(PixelInput aInput)
{
	PixelOutput output;
	float3 blurColor = (float3) 0;

	for (uint i = 0; i < kernelSize; ++i)
	{
		float2 textureCoords = aInput.uv;
		textureCoords.y += texelSize * texelOffset[i];
		float3 resource = boundTexture.SampleLevel(defaultSamplerState, textureCoords, 0).rgb;
		blurColor += resource * weights[i];
	}

	output.color = float4(blurColor.rgb, 1.f);

	return output;
}

PixelOutput PShader_Add(PixelInput aInput)
{
	float3 resourceOne = boundTexture.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;
	float3 resourceTwo = boundSecondTexture.SampleLevel(defaultSamplerState, aInput.uv, 0).rgb;

	PixelOutput output;
	output.color = float4(resourceOne.rgb + resourceTwo.rgb, 1.f);
	return output;
}