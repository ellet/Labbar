#define Pi 3.14159265359

struct VertexInput
{
    float4 position : POSITION;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
	float2 uv : TEXCOORD;
	
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
    float4 objectPosition : OBJECTPOSITION;
	
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

cbuffer TimerBuffer : register(b7)
{
    float4 time;
};

Texture2D boundTexture : register( t0 );
Texture2D boundNormalMap : register( t1 );
Texture2D depthMapTexture : register(t2);



SamplerState samplerState;
