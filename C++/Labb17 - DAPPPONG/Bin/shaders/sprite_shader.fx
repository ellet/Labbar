#include "common_sprite.fx"

struct VertexInputType
{
    float4 position : POSITION; 
    float2 tex : TEXCOORD0;
};

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	
	float2 Resolution = myResolution.xy;
	float ratio = Resolution.y / Resolution.x;

    // Change the position vector to be 4 units for proper matrix calculations.
	
    input.position.w = 1.0f;
	
	input.position.x *= ratio;
	input.position.x -= myPivot.x;
	input.position.y += myPivot.y;
	
	input.position.xy *= myRotationAndSize.yz;
	
	float2x2 theRotation = ComputeParticleRotation(myRotationAndSize.x);
	input.position.xy = mul(input.position.xy, theRotation);
	input.position.xy += myPosition;
		output.position = input.position;
    // Calculate the position of the vertex against the world, view, and projection matrices.
    //output.position = mul(input.position, worldMatrix);
    //output.position = mul(output.position, viewMatrix);
    //output.position = mul(output.position, projectionMatrix);
    
	output.tex = myUV.xy + (input.tex * myUV.z);
	output.color = myColor; 
	output.textureMappingData = myRotationAndSize.w;
	
    return output;  
}