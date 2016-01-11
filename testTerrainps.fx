float3 lightSpecular;
float3 lightDiffuse;
float3 lightAmbient;

sampler2D DiffuseSampler;

struct PS_INPUT
{
    float2 UV : TEXCOORD0;
    float3 Diffuse : TEXCOORD1;
    float3 ViewDir : TEXCOORD2;
    float3 Reflection : TEXCOORD3;
};

float4 ps_main(PS_INPUT Input) : COLOR
{
    float4 albedo = tex2D(DiffuseSampler, Input.UV);
    float3 diffuse = lightDiffuse * albedo.rgb * saturate(Input.Diffuse);

    float3 reflection = normalize(Input.Reflection);
    float3 viewDir = normalize(Input.ViewDir);
    float3 specular = 0;
    if(diffuse.x > 0){
        specular = saturate(dot(reflection, -viewDir));
        specular = pow(specular, 20.0f) * lightSpecular;
    }

    float3 ambient = lightAmbient * albedo;

    return float4(ambient + diffuse + specular, 1);
}