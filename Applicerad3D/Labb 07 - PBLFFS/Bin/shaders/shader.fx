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
};

cbuffer LightConstantBuffer : register(b1)
{
	struct DirectionLight
	{
		float4 direction;
		float4 color;
	} directionLight[1];
};

Texture2D boundAlbedo : register( t0 );
Texture2D boundSpecularMap : register( t1 );
Texture2D boundAmbient : register(t2);
Texture2D boundEmissive : register(t3);
Texture2D boundNormalMap : register(t4);
Texture2D boundMetalness : register(t5);

TextureCube cubeMap : register(t6);

static float CubeMipCountX = 8.f;

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

float RoughToSPow(float fSpecular)
{
	return (2.0f / (fSpecular * fSpecular) - 2.f);
}
static const float k0 = 0.00098f;
static const float k1 = 0.9921f;
static const float fakeLysMaxSpecularPower = (2.f / (0.0014f * 0.0014f)) - 2.f;
static const float fMaxT = (exp2(-10.f / sqrt((2.f / (0.0014f * 0.0014f)) - 2.f)) - 0.00098f) / 0.9921f;
float GetSpecPowToMip(float fSpecPow, int nMips)
{
	float fSmulMaxT = (exp2(-10.f / sqrt(fSpecPow)) - k0) / k1;

	return float(nMips - 1 - 0) * (1.0 - clamp(fSmulMaxT / fMaxT, 0.0, 1.0));
}


PixelOutputType PShader_Emissive(PixelInputType input)
{
	PixelOutputType output;

	output.color.xyz = boundEmissive.Sample(samplerState, input.uv).xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_Metalness(PixelInputType input)
{
	PixelOutputType output;
	
	output.color.xyz = boundMetalness.Sample(samplerState, input.uv).xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_Albedo(PixelInputType input)
{
	PixelOutputType output;
	
	output.color.xyz = boundAlbedo.Sample(samplerState, input.uv).xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_AmbientOcclusion(PixelInputType input)
{
	PixelOutputType output;

	output.color.xyz = boundAmbient.Sample(samplerState, input.uv).xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_NormalMap(PixelInputType input)
{
	PixelOutputType output;

	//output.color.xyz = (boundNormalMap.Sample(samplerState, input.uv).xyz * 2.f) - (1.f).xxx;
	output.color.xyz = boundNormalMap.Sample(samplerState, input.uv).xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_Specular(PixelInputType input)
{
	PixelOutputType output;

	output.color.xyz = boundSpecularMap.Sample(samplerState, input.uv).xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_Substance(PixelInputType input)
{
	float3 albedo = PShader_Albedo(input).color.xyz;
	float3 metalness = PShader_Metalness(input).color.xyz;
	float3 substance = (float3(0.04f, 0.04f, 0.04f) - (float3(0.04f, 0.04f, 0.04f) * metalness)) + albedo * metalness;


	PixelOutputType output;

	output.color.xyz = substance.xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_MetalnessAlbedo(PixelInputType input)
{
	float3 albedo = PShader_Albedo(input).color.xyz;
	float3 metalness = PShader_Metalness(input).color.xyz;
	float3 metalnessAlbedo = albedo - (albedo * metalness);
	
	PixelOutputType output;
	
	output.color.xyz = metalnessAlbedo.xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_VertexNormal(PixelInputType input)
{
	PixelOutputType output;
	output.color.xyz = normalize(input.normal.xyz);
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_VertexTangent(PixelInputType input)
{
	PixelOutputType output;
	output.color.xyz = normalize(input.tangent.xyz);
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_VertexBitangent(PixelInputType input)
{
	PixelOutputType output;
	output.color.xyz = normalize(input.bitangent.xyz);
	output.color.a = 1.f;
	return output;
}
PixelOutputType PShader_Lambert(PixelInputType input)
{
	float lambert = saturate(dot(PShader_VertexNormal(input).color.xyz, -directionLight[0].direction.xyz));

	PixelOutputType output;
	output.color.xyz = lambert.xxx;
	output.color.a = 1.f;
	return output;

}
PixelOutputType PShader_ObjectNormal(PixelInputType input)
{
	float3 normalMap = PShader_NormalMap(input).color.xyz;
	normalMap = (normalMap * float3(2.f, 2.f, 2.f)) - float3(1.f, 1.f, 1.f);
	normalMap = normalize(normalMap);

	float3 vertexNormal = PShader_VertexNormal(input).color.xyz;
	float3 vertexTangent = PShader_VertexTangent(input).color.xyz;
	float3 vertexBitangent = PShader_VertexBitangent(input).color.xyz;

	float3x3 tangentSpaceMatrix = float3x3(vertexTangent, vertexBitangent, vertexNormal);


	PixelOutputType output;
	output.color.xyz = normalize(mul(normalMap, tangentSpaceMatrix).xyz);
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_Fresnel(PixelInputType input)
{
	float3 toLight = -directionLight[0].direction.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 substance = PShader_Substance(input).color.xyz;
	float3 halfVector = normalize(toLight + toEye.xyz);

	float LdotH = dot(toLight, halfVector);
	LdotH = saturate(LdotH);
	LdotH = 1.0f - LdotH;
	LdotH = pow(LdotH, 5);
	float3 fresnel = LdotH * (1.0f - substance);
	fresnel = substance + fresnel;

	PixelOutputType output;
	output.color.xyz = fresnel.xyz;
	output.color.a = 1.f;
	return output;
}
PixelOutputType PShader_ReflectionFresnel(PixelInputType input)
{
	float specular = PShader_Specular(input).color.x;
	float3 substance = PShader_Substance(input).color.xyz;
	float3 normal = PShader_ObjectNormal(input).color.xyz;
	
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float VdotN = dot(toEye.xyz, normal);
	VdotN = saturate(VdotN);
	VdotN = 1.0f - VdotN;
	VdotN = pow(VdotN, 5);

	float3 fresnel = VdotN * (1.0f - substance);
	fresnel = fresnel / (6 - 5 * specular);
	fresnel = substance + fresnel;

	PixelOutputType output;
	output.color.xyz = fresnel.xyz;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_Visibility(PixelInputType input)
{
	float3 toLight = -directionLight[0].direction.xyz;

	float specular = PShader_Specular(input).color.x;
	float specularRemapped = (specular + 1.0f) / 2.0f;

	float3 normal = PShader_ObjectNormal(input).color.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);

	float NdotL = saturate(dot(normal, toLight));
	float NdotV = saturate(dot(normal, toEye));

	float k = specularRemapped * specularRemapped * 1.7724f;
	float G1V = NdotV * (1.0f - k) + k;
	float G1L = NdotL * (1.0f - k) + k;
	float visibility = (NdotV * NdotL) / (G1V * G1L);

	PixelOutputType output;
	output.color.xyz = visibility.xxx;
	output.color.a = 1.f;
	return output;
}
PixelOutputType PShader_Distribution(PixelInputType input)
{
	float3 toLight = -directionLight[0].direction.xyz;
	
	float specular = PShader_Specular(input).color.x;
	float3 normal = PShader_ObjectNormal(input).color.xyz;
	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 halfVector = normalize(toLight + toEye.xyz);
	float HdotN = saturate(dot(halfVector, normal));

	float m = specular * specular;
	float m2 = m* m;
	float denominator = HdotN * HdotN * (m2 - 1.f) + 1.f;
	float distribution = m2 / (3.14159 * denominator * denominator);

	PixelOutputType output;
	output.color.xyz = distribution.xxx;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_AmbientSpecularity(PixelInputType input)
{
	float3 normal = PShader_ObjectNormal(input).color.xyz;
	float specular = PShader_Specular(input).color.x;
	float3 ambientOcclusion = PShader_AmbientOcclusion(input).color.xxx;

	float3 toEye = normalize(cameraPosition.xyz - input.worldPosition.xyz);
	float3 reflectionVector = -reflect(toEye, normal);

	float fakeLysSpecularPower = RoughToSPow(specular);
	//float lysMipMap = GetSpecPowToMip(fakeLysSpecularPower, (uint)CubeMipCount.x )
	float lysMipMap = GetSpecPowToMip(fakeLysSpecularPower, (uint)CubeMipCountX);

	float3 ambientLight = cubeMap.SampleLevel(samplerState, reflectionVector.xyz, lysMipMap).xyz;
	float3 fresnel = PShader_ReflectionFresnel(input).color.xyz;

	PixelOutputType output;
	output.color.xyz = ambientLight * ambientOcclusion * fresnel;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_DirectSpecularity(PixelInputType input)
{
	float3 lightColor = directionLight[0].color.xyz;
	float3 lambert = PShader_Lambert(input).color.xxx;
	float3 fresnel = PShader_Fresnel(input).color.xyz;
	float3 distribution = PShader_Distribution(input).color.xxx;
	float3 visibility = PShader_Visibility(input).color.xxx;

	PixelOutputType output;
	output.color.xyz = lightColor * lambert * fresnel * distribution * visibility;
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_AmbientDiffuse(PixelInputType input)
{
	float3 normal = PShader_ObjectNormal(input).color.xyz;
	float3 metalnessAlbedo = PShader_MetalnessAlbedo(input).color.xyz;
	float3 ambientOcclusion = PShader_AmbientOcclusion(input).color.xxx;

	//float3 ambientLight = cubeMap.SampleLevel(samplerState, normal.xyz, (uint)CubeMipCount.x - 2).xyz;
	float3 ambientLight = cubeMap.SampleLevel(samplerState, normal.xyz, (uint)CubeMipCountX - 2).xyz;
	float3 fresnel = PShader_ReflectionFresnel(input).color.xyz;


	PixelOutputType output;
	output.color.xyz = metalnessAlbedo * ambientLight * ambientOcclusion * (float3(1.f, 1.f, 1.f) - fresnel);
	output.color.a = 1.f;
	return output;
}

PixelOutputType PShader_DirectDiffuse(PixelInputType input)
{
	float3 lightColor = directionLight[0].color.xyz;

	float3 metalnessAlbedo = PShader_MetalnessAlbedo(input).color.xyz;

	float3 lambert = PShader_Lambert(input).color.xxx;
	float3 fresnel = PShader_Fresnel(input).color.xyz;

	PixelOutputType output;
	output.color.xyz = metalnessAlbedo * lightColor * lambert * (float3(1.0f, 1.0f, 1.0f) - fresnel);
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PShader_PBL(PixelInputType input)
{
	float3 emissive = PShader_Emissive(input).color.xyz;
	float3 ambientDiffuse = PShader_AmbientDiffuse(input).color.xyz;
	float3 ambientSpecularity = PShader_AmbientSpecularity(input).color.xyz;

	float3 directDiffuse = PShader_DirectDiffuse(input).color.xyz;
	float3 directSpecularity = PShader_DirectSpecularity(input).color.xyz;


	PixelOutputType output;
	output.color.xyz = ambientDiffuse + ambientSpecularity + directDiffuse + directSpecularity + emissive;
	output.color.a = 1.0f;
	return output;
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	
	output.color.xyz = PShader_PBL(input).color.xyz;
	output.color.a = 1.0f;
	return output;
}

//PixelOutputType PShader(PixelInputType input)
//{
	//

	//return output;
//}

//PixelOutputType output;
	
	
	//old stuff
	
	//float3 sampledColor = boundTexture.Sample(samplerState, input.uv).xyz;
	//float3 sampledNormal = (boundNormalMap.Sample(samplerState, input.uv).xyz * 2.f) - (1.f).xxx;
	
	//float3 sampledAmbient = boundTexture.Sample(samplerState, input.uv).xyz;
	//float sampledMetalness = (boundMetalness.Sample(samplerState, input.uv));
	
	//float3x3 tangentSpaceMatrix = float3x3(
//		normalize(input.bitangent.xyz),
		//normalize(input.tangent.xyz),
		//normalize(input.normal.xyz)
	//);
	
	//float3 normal = mul(sampledNormal, tangentSpaceMatrix);

	//const float3 directionToLight = -directionLight[0].direction;
	
	//float lambert = saturate(dot(normal, directionToLight));
	//float3 directDiffuse = sampledColor * directionLight[0].color * lambert.xxx;

	//float ambientAmount = 0.001f;

	//output.color = float4(directDiffuse * (1.0f - ambientAmount) + sampledColor * ambientAmount, 1.0f);
	//output.color = float4(sampledMetalness, sampledMetalness, sampledMetalness, 1.f);

	//return output;
