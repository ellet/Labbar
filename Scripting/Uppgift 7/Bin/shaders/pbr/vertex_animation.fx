#include "common.fx"

cbuffer BonesBuffer : register(b2)
{
    float4x4 boneMatrices[64];
};

PixelInput VShader(VertexInput input)
{
	PixelInput output;
    
    float4x4 finalMatrix = (float4x4) 0;

    for (int i = 0; i < 4; i++)
    {
        finalMatrix += input.weights[i] * boneMatrices[input.bones[i]];
    }

	output.position = input.position;
	output.position = mul(finalMatrix, output.position);
    output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);

    float4x4 m = input.toWorld;
	output.normal = input.normal;
	output.tangent = input.tangent;
	output.bitangent = input.bitangent;
	
    output.normal = float4(mul((float3x3)finalMatrix, output.normal.xyz), 1.0f);
    output.normal = float4(mul((float3x3)m, output.normal.xyz), 1.0f);
		
    output.tangent = float4(mul((float3x3)finalMatrix, output.tangent.xyz), 1.0f);
    output.tangent = float4(mul((float3x3)m, output.tangent.xyz), 1.0f);
	
    output.bitangent = float4(mul((float3x3)finalMatrix, output.bitangent.xyz), 1.0f);
    output.bitangent = float4(mul((float3x3)m, output.bitangent.xyz), 1.0f);

    output.viewPosition = output.position.xy;
    output.viewPosition /= output.position.w;

    float4 previous = input.position;
    previous = mul(input.previousToWorld, previous);
    previous = mul(finalMatrix, previous);
    previous = mul(previousToCamera, previous);
    previous = mul(previousToProjection, previous);
    output.previousViewPosition = previous / previous.w;

	output.uv = input.uv;
    output.instanceColor = input.instanceColor;

	return output;
}
