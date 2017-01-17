#include "common.fx"

PixelInput VShader(VertexInput input)
{
	PixelInput output;

	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);

	output.normal = float4(normalize(mul((float3x3)input.toWorld, input.normal.xyz)), 1.0f);
	output.tangent = float4(normalize(mul((float3x3)input.toWorld, input.tangent.xyz)), 1.0f);
	output.bitangent = float4(normalize(mul((float3x3)input.toWorld, input.bitangent.xyz)), 1.0f);

    output.viewPosition = output.position.xy;
    output.viewPosition /= output.position.w;

    float4 previous = input.position;
    previous = mul(input.previousToWorld, previous);
    previous = mul(previousToCamera, previous);
    previous = mul(previousToProjection, previous);
    output.previousViewPosition = previous / previous.w;

	output.uv = input.uv;
    output.instanceColor = input.instanceColor;

	return output;
}
