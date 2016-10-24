#define Pi 3.14159265359

struct VertexInputType
{
    float3 position : POSITION;
    float size : SIZE;
    float4 color : COLOR;
};

struct GeometryInputType
{
    float4 position : SV_POSITION;
    float size : SIZE;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;	
    float4 color : COLOR;
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

Texture2D boundTexture : register( t0 );

SamplerState samplerState;

GeometryInputType VShader(VertexInputType input)
{
    GeometryInputType output = (GeometryInputType) 0;

    output.position = float4(input.position, 1.f);
    output.position = mul(toCamera, output.position);
    output.size = input.size;
    output.color = input.color;

    return output;
}

[maxvertexcount(4)]
void GShader(point GeometryInputType input[1], inout TriangleStream<PixelInputType> triStream)
{
    const float4 offset[4] =
    {
        { -input[0].size, input[0].size, 0, 0 },
        { input[0].size, input[0].size, 0, 0 },
        { -input[0].size, -input[0].size, 0, 0 },
        { input[0].size, -input[0].size, 0, 0 }
    };

    const float2 uv_coordinates[4] =
    {
        { 0, 1 },
        { 1, 1 },
        { 0, 0 },
        { 1, 0 }
    };

    for (int i = 0; i < 4; ++i)
    {
        PixelInputType vertex = (PixelInputType) 0;

        vertex.position = input[0].position + offset[i];
        vertex.position = mul(toProjection, vertex.position);

        vertex.uv = uv_coordinates[i];
        vertex.color = input[0].color;
        triStream.Append(vertex);
    }

    triStream.RestartStrip();
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
    output.color = input.color;
	return output;
}
