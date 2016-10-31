#include "common.fx"

PixelInput VShader(VertexInput input)
{
	PixelInput output;

	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
    output.cameraPosition = float4(output.position.xyz, 1.f);
	output.position = mul(toProjection, output.position);

    output.LastFramePosition = input.position;
    output.LastFramePosition = mul(input.oldToWorld, output.LastFramePosition);
    output.LastFramePosition = mul(toCamera, output.LastFramePosition);

	output.normal = float4(mul((float3x3)input.toWorld, input.normal.xyz), 1.0f);
	output.tangent = float4(mul((float3x3)input.toWorld, input.tangent.xyz), 1.0f);
	output.bitangent = float4(mul((float3x3)input.toWorld, input.bitangent.xyz), 1.0f);

	output.uv = input.uv;
    output.instanceColor = input.instanceColor;

	return output;
}
