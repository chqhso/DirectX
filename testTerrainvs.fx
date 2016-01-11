float4x4 matProj;
float4x4 matView;
float3 lightPosition;
float3 cameraPosition;

struct VS_INPUT
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 Texcoord : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 Position : POSITION;
    float2 Texcoord : TEXCOORD0;
    float3 Diffuse : TEXCOORD1;
    float3 ViewDir : TEXCOORD2;
    float3 Reflection : TEXCOORD3;
};

VS_OUTPUT vs_main (VS_INPUT Input)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 lightDir = Input.Position.xyz - lightPosition.xyz;
    lightDir = normalize(lightDir);

    float3 viewDir = normalize(Input.Position.xyz - cameraPosition.xyz);
    Out.ViewDir = viewDir;
    Out.Position = mul(float4(Input.Position, 1), matView);
    Out.Position = mul(Out.Position, matProj);

    Out.Diffuse = dot(-lightDir, Input.Normal);
    Out.Reflection = reflect(lightDir, Input.Normal);

    Out.Texcoord = Input.Texcoord;

    return Out;
};