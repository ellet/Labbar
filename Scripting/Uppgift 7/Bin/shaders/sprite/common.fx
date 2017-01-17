
struct VertexInputType
{
    float4 position : POSITION;
	float2 uv : TEXCOORD0;
	
	matrix toWorld : INSTANCE_MATRIX;
	float4 color : INSTANCE_COLOR;

    float2 textureTopLeft : TEXTOPLEFT;
    float2 textureSize : TEXSIZE;
};
