float4x4 matWorld;
float4x4 matProj;
float4x4 matView;
float4 lightPosition;
float3 cameraPosition;

struct VS_INPUT
{
   float3 Position : POSITION;
   float3 Normal : NORMAL;
   float2 Texcoord : TEXCOORD0;
   float4 BlendWeight : TEXCOORD1;
   float4 BlendIndex : TEXCOORD2;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION;
   float2 Texcoord : TEXCOORD0;
   float3 Diffuse : TEXCOORD1;
   float3 ViewDir : TEXCOORD2;
   float3 Reflection : TEXCOORD3;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
   VS_OUTPUT Out = (VS_OUTPUT)0;
   
   Out.Position = mul(float4(Input.Position.xyz, 1), matWorld);
   
   float3 lightDir = Out.Position.xyz - lightPosition.xyz;
   lightDir = normalize(lightDir);
   
   float3 viewDir = normalize(Out.Position.xyz - cameraPosition.xyz);
   Out.ViewDir = viewDir;
   
   Out.Position = mul(Out.Position, matView);
   Out.Position = mul(Out.Position, matProj);
   
   float3 worldNormal = mul(Input.Normal, (float3x3)matWorld);
   worldNormal = normalize(worldNormal);
   
   Out.Diffuse = dot(-lightDir, worldNormal);
   Out.Reflection = reflect(lightDir, worldNormal);
   
   Out.Texcoord = Input.Texcoord;
   
   return Out;
   
}



