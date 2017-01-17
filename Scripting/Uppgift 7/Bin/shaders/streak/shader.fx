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

Texture2D boundTexture : register(t0);

SamplerState samplerState;

GeometryInputType VShader(VertexInputType input)
{
    GeometryInputType output = (GeometryInputType) 0;

    output.position = float4(input.position, 1.f);
    //output.position = mul(worldspace, output.position);
    output.position = mul(toCamera, output.position);
    output.size = input.size;
    output.color = input.color;

    return output;
}

[maxvertexcount(4)]
void GShader(lineadj GeometryInputType input[4], inout TriangleStream<PixelInputType> triStream)
{
    float3 toEyeTailing = normalize(-(input[0].position.xyz + input[1].position.xyz) / 2.0f);
    float3 toEyeLine = normalize(-(input[1].position.xyz + input[2].position.xyz) / 2.0f);
    float3 toEyeHeading = normalize(-(input[2].position.xyz + input[3].position.xyz) / 2.0f);
    
    float3 tailingDirection = normalize(input[1].position.xyz - input[0].position.xyz);
    float3 headingDirection = normalize(input[2].position.xyz - input[3].position.xyz);
    float3 lineDirection = normalize(input[2].position.xyz - input[1].position.xyz);
    float3 lineNormal = normalize(cross(toEyeLine, lineDirection));

    float3 halfVec1 = normalize(normalize(cross(toEyeTailing, tailingDirection)) + lineNormal);
    float3 halfVec2 = normalize(normalize(cross(headingDirection, toEyeHeading)) + lineNormal);

    const float lineIndexOffset[4] =
    {
        1,
        2,
        1,
        2
    };

    const float2 uv_coordinates[4] =
    {
        { 0, 1 },
        { 1, 1 },
        { 0, 0 },
        { 1, 0 }
    };

    const float3 normal[4] =
    {
        -halfVec1,
        -halfVec2,
		halfVec1,
        halfVec2
    };

    for (int i = 0; i < 4; ++i)
    {
        PixelInputType vertex = (PixelInputType) 0;

        vertex.position.xyz = input[lineIndexOffset[i]].position.xyz + (normal[i] * input[lineIndexOffset[i]].size);
        vertex.position.w = 1.f;
        vertex.position = mul(toProjection, vertex.position);

        vertex.uv = uv_coordinates[i];
        vertex.color = input[i].color;
        vertex.color.a = 1.f;
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
