struct VertexInputType
{
    float4 position : POSITION;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	float2 uv : TEXCOORD;
	
	matrix toWorld : INSTANCE_MATRIX;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 worldPosition : POSITION;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
    float2 uv : TEXCOORD;
};

struct PixelOutputType
{
	float4 color : SV_TARGET;
};


cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
	matrix toProjection;
	float4 cameraPosition;
}

cbuffer LightBuffer : register(b1)
{
	float4 LightDirection;
	float4 LightColor;
}

Texture2D boundTexture : register( t0 );
Texture2D normalMap : register( t1 );
SamplerState samplerState;

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	output.position = input.position;
	output.position = mul(input.toWorld, output.position);
	output.worldPosition = output.position;
	output.position = mul(toCamera, output.position);
	output.position = mul(toProjection, output.position);
	
	output.normal = float4(mul((float3x3)input.toWorld, input.normal.xyz), 1.0f);
	output.tangent = float4(mul((float3x3)input.toWorld, input.tangent.xyz), 1.0f);
	output.bitangent = float4(mul((float3x3)input.toWorld, input.bitangent.xyz), 1.0f);
	output.uv = input.uv;
	
	
    return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	
	float3 sampledColor = boundTexture.Sample(samplerState, input.uv).xyz;
	float3 sampledNormal = normalMap.Sample(samplerState, input.uv).xyz;
	
	float3 AmbientDiffuse = sampledColor.rgb * 0.000001f;
	
	sampledNormal = (sampledNormal * float3(2.f,2.f,2.f) - float3(1.f, 1.f, 1.f));
	normalize(sampledNormal);
	
	float3 VertexNormal = normalize(input.normal.xyz);
	float3 VertexTangent = normalize(input.tangent.xyz);
	float3 VertexBitangent = normalize(input.bitangent.xyz);
	
	float3x3 TangentSpaceMatrix = float3x3(VertexBitangent, VertexTangent, VertexNormal);
	
	sampledNormal = normalize(mul(sampledNormal, TangentSpaceMatrix).xyz);
	
	float Lambert = saturate(dot(sampledNormal, -LightDirection.xyz));
	float3 directDiffuse = sampledColor.rgb * LightColor.rgb * Lambert.xxx;
	
	float3 totalLight = directDiffuse + AmbientDiffuse;
	
	output.color = float4(totalLight.rgb, 1.0f);
	//output.color = sampledColor;//float4(normal, 1.0f); //* LightColor;
	//output.color = float4(sampledNormal, 1.0f); //* LightColor;
	
	return output;
}
