// ----------------------------------------- Header ------------------------------------------
#ifndef SFX_HLSL_5
	#define SFX_HLSL_5
#endif 
#ifndef _MAYA_
	#define _MAYA_
#endif 



#ifndef half 
	#define half float 
	#define half2 float2 
	#define half3 float3 
	#define half4 float4 
#endif 



// ----------------------------------- Per Frame --------------------------------------
cbuffer UpdatePerFrame : register(b0)
{
	float time : Time < string UIWidget = "None"; >;

	bool MayaHwFogEnabled : HardwareFogEnabled < string UIWidget = "None"; > = false; 
	int MayaHwFogMode : HardwareFogMode < string UIWidget = "None"; > = 0; 
	float MayaHwFogStart : HardwareFogStart < string UIWidget = "None"; > = 0.0; 
	float MayaHwFogEnd : HardwareFogEnd < string UIWidget = "None"; > = 100.0; 
	float MayaHwFogDensity : HardwareFogDensity < string UIWidget = "None"; > = 0.1; 
	float4 MayaHwFogColor : HardwareFogColor < string UIWidget = "None"; > = { 0.5, 0.5, 0.5, 1.0 }; 


	float4x4 viewPrj : ViewProjection < string UIWidget = "None"; >;

};

// --------------------------------------- Per Object -----------------------------------------
cbuffer UpdatePerObject : register(b1)
{
	float4x4 world : World < string UIWidget = "None"; >;

	float4x4 wvp : WorldViewProjection < string UIWidget = "None"; >;

};

// ---------------------------------------- Textures -----------------------------------------
Texture2D greyPack_mediantga
<
	string ResourceName = "greyPack_median.tga";
	string UIName = "greyPack_mediantga";
	string ResourceType = "2D";
	string UIWidget = "FilePicker";
>;

SamplerState MMMLWWWSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};


// -------------------------------------- ShaderVertex --------------------------------------
struct APPDATA
{
	float3 Position : POSITION;
	float2 map1 : TEXCOORD0;
};

struct SHADERDATA
{
	float4 Position : SV_Position;
	float4 map1 : TEXCOORD0;
	half3 FogFactor : TEXCOORD1;
	float4 WorldPosition : TEXCOORD2;
};

SHADERDATA ShaderVertex(APPDATA IN)
{
	SHADERDATA OUT;

	OUT.Position = float4(IN.Position, 1);
	float MulOp = (time * 2.0);
	float MulOp98 = (sin(MulOp) * 0.03);
	float3 MulOp94 = (OUT.Position.xyz * (1.0 + MulOp98));
	float4 VectorConstruct = float4(MulOp94.x, MulOp94.y, MulOp94.z, 1.0);
	OUT.Position = VectorConstruct;
	float4 OutUVs = float4(IN.map1.x, IN.map1.y, 0.0, 0.0);
	OUT.map1 = OutUVs;
	OUT.WorldPosition = (mul(float4(IN.Position,1), world));
	float4 _HPosition = mul( float4(OUT.WorldPosition.xyz, 1), viewPrj ); 
	float fogFactor = 0.0; 
	if (MayaHwFogMode == 0) { 
				fogFactor = saturate((MayaHwFogEnd - _HPosition.z) / (MayaHwFogEnd - MayaHwFogStart)); 
	} 
	else if (MayaHwFogMode == 1) { 
				fogFactor = 1.0 / (exp(_HPosition.z * MayaHwFogDensity)); 
	} 
	else if (MayaHwFogMode == 2) { 
				fogFactor = 1.0 / (exp(pow(_HPosition.z * MayaHwFogDensity, 2))); 
	} 
	OUT.FogFactor = float3(fogFactor, fogFactor, fogFactor); 

	float4 WVSpace = mul(OUT.Position, wvp);
	OUT.Position = WVSpace;

	return OUT;
}

// -------------------------------------- ShaderPixel --------------------------------------
struct PIXELDATA
{
	float4 Color : SV_Target;
};

PIXELDATA ShaderPixel(SHADERDATA IN)
{
	PIXELDATA OUT;

	float3 Color = float3(1.0,0.5003,0.0);
	float2 NormOp = normalize((IN.map1.xy - float2(0.5,0.5)));
	float MulOp = (time * 0.7);
	float AddOp = (MulOp + NormOp.y);
	float2 VectorConstruct = float2(NormOp.x, AddOp);
	float4 Sampler = greyPack_mediantga.Sample(MMMLWWWSampler, float2(VectorConstruct.xy.x, 1-VectorConstruct.xy.y));
	float MulOp119 = (time * 0.4);
	float AddOp130 = (NormOp.x + MulOp119);
	float2 VectorConstruct124 = float2(AddOp130, NormOp.y);
	float4 Sampler133 = greyPack_mediantga.Sample(MMMLWWWSampler, float2(VectorConstruct124.xy.x, 1-VectorConstruct124.xy.y));
	float LengthOp = length((IN.map1.xy - float2(0.5,0.5)));
	float MulOp72 = (LengthOp * 2.18472);
	float OneMinusOp = (1.0 - MulOp72);
	float MulOp74 = (OneMinusOp * 3.0);
	float MulOp76 = (OneMinusOp * 10.0);
	float SubOp = (MulOp76 - 1.93055);
	float SubOp82 = (saturate(MulOp74) - saturate(SubOp));
	float PowOp = pow(SubOp82, 3.0);
	float MulOp118 = (PowOp * 10.0);
	float MulOp103 = ((Sampler.xyz.x * Sampler133.xyz.z) * MulOp118);
	float3 MulOp121 = (Color.xyz * MulOp103);
	float4 VectorConstruct104 = float4(MulOp121.x, MulOp121.y, MulOp121.z, 1.0);
	if (MayaHwFogEnabled) { 
		float fogFactor = (1.0 - IN.FogFactor.x) * MayaHwFogColor.a; 
		VectorConstruct104.rgb	= lerp(VectorConstruct104.rgb, MayaHwFogColor.rgb, fogFactor); 
	} 

	OUT.Color = VectorConstruct104;

	return OUT;
}

// -------------------------------------- technique T0 ---------------------------------------
technique11 T0
{
	pass P0
	<
		string drawContext = "colorPass";
	>
	{
		SetVertexShader(CompileShader(vs_5_0, ShaderVertex()));
		SetPixelShader(CompileShader(ps_5_0, ShaderPixel()));
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetGeometryShader(NULL);
	}

}

