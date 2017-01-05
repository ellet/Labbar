// ----------------------------------------- Header ------------------------------------------
#ifndef SFX_HLSL_3
	#define SFX_HLSL_3
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
float time : Time < string UIWidget = "None"; >;

float4x4 viewI : ViewInverse < string UIWidget = "None"; >;

	bool MayaHwFogEnabled : HardwareFogEnabled < string UIWidget = "None"; > = false; 
	int MayaHwFogMode : HardwareFogMode < string UIWidget = "None"; > = 0; 
	float MayaHwFogStart : HardwareFogStart < string UIWidget = "None"; > = 0.0; 
	float MayaHwFogEnd : HardwareFogEnd < string UIWidget = "None"; > = 100.0; 
	float MayaHwFogDensity : HardwareFogDensity < string UIWidget = "None"; > = 0.1; 
	float4 MayaHwFogColor : HardwareFogColor < string UIWidget = "None"; > = { 0.5, 0.5, 0.5, 1.0 }; 


float4x4 viewPrj : ViewProjection < string UIWidget = "None"; >;


// --------------------------------------- Per Object -----------------------------------------
float4x4 wvp : WorldViewProjection < string UIWidget = "None"; >;

float4x4 world : World < string UIWidget = "None"; >;


// ---------------------------------------- Textures -----------------------------------------
Texture2D greyPack_mediantga
<
	string ResourceName = "greyPack_median.tga";
	string UIName = "greyPack_mediantga";
	string ResourceType = "2D";
	string UIWidget = "FilePicker";
>;

sampler2D greyPack_mediantgaSampler = sampler_state 
{
	Texture = <greyPack_mediantga>;
	MinFilter = MIN_MAG_MIP_LINEAR;
	MagFilter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};

Texture2D hexa_penta_w_alphatga
<
	string ResourceName = "hexa_penta_w_alpha.tga";
	string UIName = "hexa_penta_w_alphatga";
	string ResourceType = "2D";
	string UIWidget = "FilePicker";
>;

sampler2D hexa_penta_w_alphatgaSampler = sampler_state 
{
	Texture = <hexa_penta_w_alphatga>;
	MinFilter = MIN_MAG_MIP_LINEAR;
	MagFilter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};


// -------------------------------------- ShaderVertex --------------------------------------
struct APPDATA
{
	float3 Position : POSITION;
	float2 map1 : TEXCOORD0;
	float3 Normal : NORMAL;
};

struct SHADERDATA
{
	float4 Position : POSITION;
	float4 ScreenPosition : TEXCOORD0;
	float4 map1 : TEXCOORD1;
	float4 WorldPosition : TEXCOORD2;
	float4 Normal : TEXCOORD3;
	half3 FogFactor : TEXCOORD4;
};

SHADERDATA ShaderVertex(APPDATA IN)
{
	SHADERDATA OUT;

	OUT.Position = float4(IN.Position, 1);
	float MulOp = (time * 2.0);
	float MulOp184 = (sin(MulOp) * 0.03);
	float3 MulOp188 = (OUT.Position.xyz * (1.0 + MulOp184));
	float4 VectorConstruct = float4(MulOp188.x, MulOp188.y, MulOp188.z, 1.0);
	OUT.Position = VectorConstruct;
	float4 WorldViewSpace = mul(OUT.Position, wvp);
	OUT.ScreenPosition = WorldViewSpace;
	float4 OutUVs = float4(IN.map1.x, IN.map1.y, 0.0, 0.0);
	OUT.map1 = OutUVs;
	float4 WorldPos = mul(OUT.Position, world);
	OUT.WorldPosition = WorldPos;
	float3 MulOp62 = mul(IN.Normal, ((float3x3)world));
	float3 NormalN = normalize(MulOp62);
	float4 WorldNormal = float4(NormalN.x, NormalN.y, NormalN.z, 1.0);
	OUT.Normal = WorldNormal;
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
	float4 Color : COLOR0;
};

PIXELDATA ShaderPixel(SHADERDATA IN)
{
	PIXELDATA OUT;

	float3 Color = float3(1.0,0.5003,0.0);
	float MulOp = (time * 0.5);
	float2 AddOp = ((IN.ScreenPosition.xy / IN.ScreenPosition.w) + 1.0);
	float2 MulOp143 = (AddOp * 0.5);
	float NegateOp = -(MulOp143.y);
	float2 VectorConstruct = float2(MulOp143.x, NegateOp);
	float2 MulOp152 = (VectorConstruct.xy * float2(1.6, 0.9));
	float AddOp155 = (MulOp + MulOp152.x);
	float MulOp165 = (time * 0.5);
	float AddOp164 = (MulOp165 + MulOp152.y);
	float2 VectorConstruct156 = float2(AddOp155, AddOp164);
	float4 Sampler = tex2D(greyPack_mediantgaSampler, float2(VectorConstruct156.xy.x, 1-VectorConstruct156.xy.y));
	float4 Sampler77 = tex2D(hexa_penta_w_alphatgaSampler, float2(IN.map1.xy.x, 1-IN.map1.xy.y));
	float3 CameraPosition = viewI[3].xyz;
	float3 CamVec = (CameraPosition - IN.WorldPosition.xyz);
	float3 CamVecNorm = normalize(CamVec);
	float3 NormOp = normalize(IN.Normal.xyz);
	float PowOp = pow(dot(CamVecNorm, NormOp), 0.476038);
	float MulOp102 = ((1.0 - PowOp) * 2.98913);
	float SubOp = (MulOp102 - 0.652588);
	float MulOp103 = (Sampler77.w * saturate(SubOp));
	float MulOp161 = ((Sampler.xyz.y * MulOp103) * 2.0);
	float3 MulOp38 = (Color.xyz * MulOp161);
	float4 VectorConstruct37 = float4(MulOp38.x, MulOp38.y, MulOp38.z, MulOp161);
	if (MayaHwFogEnabled) { 
		float fogFactor = (1.0 - IN.FogFactor.x) * MayaHwFogColor.a; 
		VectorConstruct37.rgb	= lerp(VectorConstruct37.rgb, MayaHwFogColor.rgb, fogFactor); 
	} 

	OUT.Color = VectorConstruct37;

	return OUT;
}

// -------------------------------------- technique T0 ---------------------------------------
technique T0
{
	pass P0
	{
		VertexShader = compile vs_3_0 ShaderVertex();
		PixelShader = compile ps_3_0 ShaderPixel();
	}

}

