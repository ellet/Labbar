struct VertexInputType
{
    float4 position : POSITION;
	float size : SIZE;
	float alpha : ALPHA;
};

struct GeometryInputType
{
    float4 position : SV_POSITION;
	float size : SIZE;
	float alpha : ALPHA;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
	float alpha : ALPHA;
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
	
	float ambient;
	float3 ambientPadding;
};

cbuffer WorldBuffer : register(b2)
{
	matrix toWorld;
}

SamplerState samplerState;

GeometryInputType VShader(VertexInputType input)
{
    GeometryInputType output;
	
	output.position = input.position;
	output.position = mul(toCamera, float4(output.position.xyz, 1.f));
	output.size = input.size;
	output.alpha = input.alpha;
	
    return output;
}

[maxvertexcount(4)]
void GShader(line GeometryInputType input[2], inout TriangleStream<PixelInputType> triStream)
{
    float3 lineDir = normalize(input[1].position.xyz - input[0].position.xyz);
    float3 toEye = normalize(- input[0].position.xyz);
    float3 normal = normalize(cross(toEye, lineDir.xyz));
	
    const float2 uv_coordinates[4] =
    {
        { 0, 1 },
        { 1, 1 },
        { 0, 0 },
        { 1, 0 }
    };

    const float lineIndexOffset[4] =
    {
        0.f,
        1.f,
        0.f,
        1.f
    };

    const float normalFlipper[4] =
    {
        -1.f,
        -1.f,
        1.f,
        1.f
    };

	
	for(int i = 0; i < 4; ++i)
	{
		PixelInputType vertex = (PixelInputType)0;
        vertex.position.xyz = input[lineIndexOffset[i]].position.xyz + (normal * normalFlipper[i] * input[lineIndexOffset[i]].size);
        vertex.position.w = 1.f;
		vertex.position = mul(toProjection, vertex.position);

		vertex.texCoord = uv_coordinates[i];
		vertex.alpha = input[0].alpha;
		
		triStream.Append(vertex);
	}
	
	triStream.RestartStrip();
}

PixelOutputType PShader(PixelInputType input)
{
	PixelOutputType output;
	
	output.color = float4(1.f, 0.f, 0.f, 1.f);
	
	return output;
}
