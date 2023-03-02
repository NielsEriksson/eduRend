cbuffer CameraLigthBuffer : register(b0)
{
	float4 CameraPos;
	float4 LightPos;
};
cbuffer MaterialBuffer : register(b1)
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
}
Texture2D texDiffuse : register(t0);
Texture2D texNormal : register(t1);
SamplerState texSampler : register(s0);



struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float2 TexCoord : TEX;
	float3 WorldPos  :  POSITION0;

};

//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{
	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	float3 T = normalize(input.Tangent);
	float3 B = normalize(input.Binormal);
	float3 N = normalize(input.Normal);
	float3x3 TBN = transpose(float3x3(T, B, N));

	float3 NormalSampler = texNormal.Sample(texSampler, input.TexCoord).xyz;

	float3 NewNormal = NormalSampler * 2 - 1;
	float3 WorldSpaceNormal = normalize(mul(TBN, NewNormal));

	float3 V = normalize(CameraPos.xyz - input.WorldPos);
	float3 L = normalize(LightPos.xyz - input.WorldPos);


	

	float3 R = normalize(reflect(-L, WorldSpaceNormal));

	float4 AmbientVector = Ambient* 0.003f;
	float4 DiffuseVector = texDiffuse.Sample(texSampler, input.TexCoord) * max(0.0f, dot(L, WorldSpaceNormal));
	float4 SpecularVector = Specular * pow(max(0.0f, dot(R, V)), 50.0f);
	//return float4(WorldSpaceNormal * 0.5 + 0.5, 1);
	return ( AmbientVector+ DiffuseVector + SpecularVector);
	


	
	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
//	return float4(input.TexCoord, 0, 1);
}