#define Pi 3.14159265359

struct VertexInputType
{
    float4 transform : TRANSFORM;
    float3 position : POSITION;
    float size : SIZE;
    float4 color : COLOR;
	float4 uv : TEXCOORD;
};

struct GeometryInputType
{
   //float4 position : SV_POSITION;
    float2x2 transform : TRANSFORM;
    float4 position : POSITION;
    float size : SIZE;
    float4 color : COLOR;
	float4 uv : TEXCOORD;
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

    float4 paddedPos = float4(input.position, 1.f);

    output.transform._11_12_21_22 = input.transform.rgba;
    output.position = mul(toCamera, paddedPos);
    output.size = input.size;
    output.color = input.color;
	output.uv = input.uv;

    return output;
}

[maxvertexcount(4)]
void GShader(point GeometryInputType input[1], inout TriangleStream<PixelInputType> triStream)
{
    //ratio for non square particles :|
    float ratio = (input[0].uv.w) / (input[0].uv.z);

    float xExtrudes = input[0].size;
    float yExtrudes = input[0].size * ratio;

    float2 pos0 = { -xExtrudes, yExtrudes };
    float2 pos1 = { xExtrudes, yExtrudes };
    float2 pos2 = { -xExtrudes, -yExtrudes };
    float2 pos3 = { xExtrudes, -yExtrudes };

    pos0 = mul(input[0].transform, pos0);
    pos1 = mul(input[0].transform, pos1);
    pos2 = mul(input[0].transform, pos2);
    pos3 = mul(input[0].transform, pos3);

    const float4 offset[4] =
    {
        { pos0, 0, 0 },
        { pos1, 0, 0 },
        { pos2, 0, 0 },
        { pos3, 0, 0 }
    };

	//Make 0-1 Rectangle from uv coords, containing a position and width/height.
    const float2 uv_coordinates[4] =
    {
		{ input[0].uv.x, input[0].uv.y },
		{ input[0].uv.x + input[0].uv.z, input[0].uv.y },
		{ input[0].uv.x, input[0].uv.y + input[0].uv.w },
		{ input[0].uv.x + input[0].uv.z, input[0].uv.y + input[0].uv.w }
    };

    //Create dat particle
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
	output.color = boundTexture.Sample(samplerState, input.uv);// input.color;
    output.color *= input.color;
	return output;
}
