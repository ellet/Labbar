#define Pi 3.14159265359

struct VertexInput
{
    float4 position : POSITION;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
    uint4 bones : BONES;
    float4 weights : WEIGHTS;
    float2 uv : TEXCOORD0;
    float2 padding : TEXCOORD1;
	
    matrix toWorld : INSTANCE_MATRIX;
	matrix previousToWorld : PREVIOUS_INSTANCE_MATRIX;
    float4 instanceColor : INSTANCE_COLOR;
};

struct PixelInput
{
    float4 position : SV_POSITION;

    float2 viewPosition : VIEWPOS;
    float2 previousViewPosition : PREVIOUSVIEWPOS;

	float4 worldPosition : POSITION;
	
	float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	
    float2 uv : TEXCOORD;
    float4 instanceColor : INSTANCE_COLOR;
};

struct PixelOutput
{
    float4 color : SV_TARGET0;
	float4 velocity : SV_TARGET1;
};

cbuffer CameraCBuffer : register(b0)
{
	matrix toCamera;
    matrix toProjection;

    matrix previousToCamera;
    matrix previousToProjection;

	float4 cameraPosition;
};

cbuffer LightConstantBuffer : register(b1)
{
	struct DirectionLight
	{
		float4 direction;
		float3 color;
		float intensity;

        matrix worldToLightSpace;
    } directionLight[1];
	    
    struct PointLight
    {
        float3 position;
        float radius;
        float3 color;
        float intensity;
    } pointLight[8];
    
	float ambient;
	float3 _ambientPadding;

	uint cubeMipCount;
	uint3 _cubePadding;
};

Texture2D boundTexture : register( t0 );
Texture2D boundNormalMap : register( t1 );
Texture2D boundRoughnessMap : register(t2);
Texture2D boundAmbientOcclusionMap : register(t3);
Texture2D boundEmissiveMap : register(t4);
Texture2D boundMetalnessMap : register(t5);
TextureCube boundCubeMap : register(t6);
Texture2D boundShadowMap : register(t7);

SamplerState samplerState;
