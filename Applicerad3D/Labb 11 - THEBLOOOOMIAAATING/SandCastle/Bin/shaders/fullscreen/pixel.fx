

#include "common.fx"


PixelOutput Luminance(PixelInput aInput)
{
	float bloomCutOff = 0.3f;

	float3 resource = boundTexture.SampleLevel(samplerState, aInput.uv, 0).rgb;
	
	float3 relativeLuminace = (float3) 0;
	
	relativeLuminace.r = 0.2126f;
	relativeLuminace.g = 0.7152;
	relativeLuminace.b = 0.0722f;

	float luminance = resource.r * relativeLuminace.r + resource.g * relativeLuminace.g + resource.b * relativeLuminace.b;
	luminance = saturate(luminance - bloomCutOff);

	float3 resourceLuminance = resource * luminance * (1 / bloomCutOff);

	PixelOutput tempOutput;
	//tempOutput.color = float4(resourceLuminance.xxx, 1.f);
	tempOutput.color = float4(resourceLuminance.rgb, 1.f);

	return tempOutput;
}

SamplerState testSampleState;

PixelOutput AddToTexturesToTarget(PixelInput aInput)
{
	float3 SampledColor1 = boundTexture.SampleLevel(testSampleState, aInput.uv, 0).rgb;
	float3 SampledColor2 = boundSecondTexture.SampleLevel(testSampleState, aInput.uv, 0).rgb;


	PixelOutput tempOutput;
	tempOutput.color = float4(SampledColor1.rgb + SampledColor2.rgb, 1.f);
	//tempOutput.color = float4(SampledColor1.rgb, 1.f);

	return tempOutput;
}


static const float texelSize = 1.0f / 256.0f;

//static const uint kernelSize = 5;
//static float Kernel[kernelSize] = { 0.06136f, 0.24477f, 0.38774f, 0.24477f, 0.06136f };
//static float TexelOffset[kernelSize] = { -2.0f, -1.0f, 0.0f, 1.0f, 2.0f };

static const uint kernelSize = 21;
static const float Kernel[kernelSize] = { 0.011254f, 0.016436f, 0.023066f, 0.031105f, 0.040306f, 0.050187f, 0.060049f, 0.069041f, 0.076276f, 0.080977f, 0.082607f, 0.080977f, 0.076276f, 0.069041f, 0.060049f, 0.050187f, 0.040306f, 0.031105f, 0.023066f, 0.016436f, 0.011254f };
static const float TexelOffset[kernelSize] = { -10.f, -9.f, -8.f, -7.f, -6.f, -5.f, -4.f, -3.f, -2.f, -1.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f };


PixelOutput GaussianBlurHorizontal(PixelInput aInput)
{
  
	float3 blurColor = (float3) 0;

	for (uint iKernel = 0; iKernel < kernelSize; ++iKernel)
	{
		float2 texureCord = aInput.uv;
		texureCord.x += texelSize * TexelOffset[iKernel];
		float3 resource = boundTexture.SampleLevel(testSampleState, texureCord, 0).rgb;
		blurColor += resource * Kernel[iKernel];
	}


	PixelOutput tempOutput;
	tempOutput.color = float4(blurColor.rgb, 1.f);

	return tempOutput;
}

PixelOutput GaussianBlurVertical(PixelInput aInput)
{
	float3 blurColor = (float3) 0;

	for (uint iKernel = 0; iKernel < kernelSize; ++iKernel)
	{
		float2 texureCord = aInput.uv;
		texureCord.y += texelSize * TexelOffset[iKernel];
		float3 resource = boundTexture.SampleLevel(testSampleState, texureCord, 0).rgb;
		blurColor += resource * Kernel[iKernel];
	}


	PixelOutput tempOutput;
	tempOutput.color = float4(blurColor.rgb, 1.f);

	return tempOutput;
}

PixelOutput CopyToTarget(PixelInput aInput)
{
	float3 SampledColor = boundTexture.SampleLevel(testSampleState, aInput.uv, 0).rgb;

	PixelOutput tempOutput;
	tempOutput.color = float4(SampledColor.rgb, 1.f);

	return tempOutput;
}

