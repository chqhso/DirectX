float4x4 matWorld;
float4x4 matProj;
float4x4 matView;
float4 lightPosition;
float4 cameraPosition;
//float4x4 matPal[50];

struct VS_INPUT
{
   float4 Position : POSITION;
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
   
   //float3 p;
   //float3 p2 = float3(0, 0, 0);
   
   // first matPal
   //p = mul(float4(Input.Position, 1), matPal[Input.BlendIndex.x]);   // p = v * mat[index1]
   //p *= Input.BlendWeight.x;                                         // p = p * weight[index1]
   //p2 = float4(p, 1);                                                // p2 = p2 + p

   // second matPal
   //p = mul(float4(Input.Position, 1), matPal[Input.BlendIndex.y]);   // p = v * mat[index2]
   //p *= Input.BlendWeight.y;                                         // p = p * weight[index2]
   //p2 += float4(p, 1);                                                // p2 = p2 + p

   // third matPal
   //p = mul(float4(Input.Position, 1), matPal[Input.BlendIndex.z]);   // p = v * mat[index3]
   //p *= Input.BlendWeight.z;                                         // p = p * weight[index3]
   //p2 += float4(p, 1);                                                // p2 = p2 + p

   // fourth matPal
   //p = mul(float4(Input.Position, 1), matPal[Input.BlendIndex.w]);   // p = v * mat[index4]
   //p *= Input.BlendWeight.w;                                         // p = p * weight[index4]
   //p2 += float4(p, 1);                                                // p2 = p2 + p

   //p = mul(float4(p2, 1), (float4x3)matView);
   
   //Out.Position = mul(float4(p2, 1), matWorld);
   
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



