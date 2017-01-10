struct VertexInput
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

cbuffer BloomBufferData : register(b4)
{
    float bloomAmount;
    float modifyBloom;
    float xPos;
    float yPos;
};
Texture2D resourceTextureOne : register(t0);
Texture2D resourceTextureTwo : register(t1);