#define Pi 3.14159265359

struct VertexInputType
{
    float3 worldPosition : POSITION;
    float size : SIZE;
    float4 color : COLOR;
};

struct GeometryInputType
{
    float3 screenPosition : POSITION;
    float size : SIZE;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
    float radius : RADIUS;
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

cbuffer VariousResourcesCBuffer : register(b1)
{
    float deltaTime;
    float runTime;
    float2 trash;
};

Texture2D boundTexture : register( t0 );

SamplerState samplerState;

GeometryInputType VShader(VertexInputType input)
{
    GeometryInputType output = (GeometryInputType) 0;

    float4 padded = float4(input.worldPosition, 1);
    output.screenPosition = mul(toCamera, padded).xyz;
    output.color = input.color;
    output.size = input.size;

    return output;
}

[maxvertexcount(4)]
void GS_Plane(point GeometryInputType input[1], inout TriangleStream<PixelInputType> triStream)
{
    float extrudes = input[0].size;

    float2 pos0 = { -extrudes, extrudes };
    float2 pos1 = { extrudes, extrudes };
    float2 pos2 = { -extrudes, -extrudes };
    float2 pos3 = { extrudes, -extrudes };

    const float4 offset[4] =
    {
        { pos0, 0, 0 },
        { pos1, 0, 0 },
        { pos2, 0, 0 },
        { pos3, 0, 0 }
    };

    const float2 uv_coordinates[4] =
    {
        { 0, 0},
        { 1 ,0},
        { 0, 1 },
        { 1, 1 }
    };

    for (int i = 0; i < 4; ++i)
    {
        PixelInputType vertex = (PixelInputType) 0;
        vertex.radius = extrudes;

        float4 padded = float4(input[0].screenPosition, 1);
        vertex.position = padded + offset[i];
        vertex.position = mul(toProjection, vertex.position);
        vertex.uv = uv_coordinates[i];

        vertex.color = input[0].color;
        triStream.Append(vertex);
    }

    triStream.RestartStrip();
}

PixelOutputType PS_StandardVisualEffect(PixelInputType input)
{
	PixelOutputType output;

    float movingSpeed = 4.0;
    float2 modifiedUVs = input.uv + (runTime * movingSpeed);

    float distancePercent = length(float2(0.5, 0.5) - input.uv);
    float outerRadius = length(float2(0.5, 0.5) - input.uv);
    output.color = input.color;
    output.color.a *= sin(distancePercent);
    output.color.a = clamp(output.color.a, 0.0, 1.0);

    output.color.b = sin(length(modifiedUVs));

	return output;
}
