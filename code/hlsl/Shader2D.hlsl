#include "Fog.hlsl"
#include "Light.hlsl"

float4x4 g_LightView : VIEW;
float4x4 g_LightProj : PROJECTION;

float3 g_light;

float3 g_lightVec[3];
float4 g_color[3];

texture g_ShadowMap;
sampler g_ShadowSampler =
sampler_state
{
    Texture = <g_ShadowMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_PositionMap;
sampler g_PositionSampler =
sampler_state
{
    Texture = <g_PositionMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_NormalMap;
sampler g_NormalSampler =
sampler_state
{
    Texture = <g_NormalMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_DiffuseMap;
sampler g_DiffuseSampler =
sampler_state
{
    Texture = <g_DiffuseMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_SpecularMap;
sampler g_SpecularSampler =
sampler_state
{
    Texture = <g_SpecularMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

struct VS_INPUT
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float4 color : COLOR0;
};

struct PS_INPUT
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float4 color : COLOR0;
};


struct OM_INPUT
{
    float4 color : COLOR0;
};

float3 ReconstructWorldPositionFromDepth(in float2 textureCoord, in float depth, in float4x4 inverseViewProjection)
{
    float4 projectedPosition = float4(textureCoord.xy * 2.0 - float2(1.0, 1.0), depth, 1.0);

    float4 position = mul(inverseViewProjection, projectedPosition);
    return position.xyz / position.w;
}

PS_INPUT vs(VS_INPUT input)
{
    PS_INPUT output;

    output.position = input.position;

    output.tex = input.tex;

    output.color = input.color;

    return output;
}

OM_INPUT ps(PS_INPUT input)
{
    OM_INPUT output = (OM_INPUT) 0;

    output.color = input.color;

    return output;
}

OM_INPUT Texps(PS_INPUT input)
{
    OM_INPUT output = (OM_INPUT) 0;

    float3 normal = (tex2D(g_NormalSampler, input.tex) * 2.0f) - 1.0f;
    float bright;
    float4 shadow, brightColor, diffuse, col = float4(0,0,0,0);

    for (int count = 0; count < 3; count++)
    {
        bright = max(-dot(normal, g_lightVec[count]), 0);

        shadow = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), g_color[count], bright);

        col += shadow;
    }

    col.r = min(col.r, 1.0f);
    col.g = min(col.g, 1.0f);
    col.b = min(col.b, 1.0f);
    col.a = min(col.a, 1.0f);
    diffuse = tex2D(g_DiffuseSampler, input.tex) * col;
   // bright = max(-dot(normal, float3(1.0f, -1.0f, -0.5f)), 0);

   // shadow = lerp(float4(0.2f, 0.2f, 0.2f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f), bright);
   //// shadow = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), float4(0.0f, 0.0f, 0.0f, 1.0f), bright);

   // diffuse = tex2D(g_DiffuseSampler, input.tex) * shadow;

    float4 pos = tex2D(g_PositionSampler, input.tex);

    diffuse += PointLight(pos.xyz, normal);

    output.color = (diffuse * input.color) + tex2D(g_SpecularSampler, input.tex);

    float4 depth = mul(mul(pos, g_LightView), g_LightProj);
    // ライト目線によるZ値の再算出
    float ZValue = depth.z / depth.w;
   
   // テクスチャ座標に変換
    float2 TransTexCoord;
    TransTexCoord.x = (1.0f + depth.x / depth.w) * 0.5f;
    TransTexCoord.y = (1.0f - depth.y / depth.w) * 0.5f;
   
   // 同じ座標のZ値を抽出
    //float SM_Z = tex2D(g_ShadowSampler, TransTexCoord).x;
    depth = tex2D(g_ShadowSampler, TransTexCoord);
    float SM_Z = depth.r + (depth.g + (depth.b + depth.a / 256.0f) / 256.0f) / 256.0f;;
   
   // 算出点がシャドウマップのZ値よりも大きければ影と判断
    if (ZValue > SM_Z + 0.006f )
    {
        output.color.rgb *= 0.5f;
    }

  //  output.color += FogLinear(pos);

    return output;
}

technique T0
{
    pass P0
    {
        AlphaTesTEnable = TRUE;
        AlphaBlendEnable = TRUE;
        ZEnable = TRUE;
        CullMode = CCW;
        ShadeMode = GOURAUD;

        VertexShader = compile vs_3_0 vs();
        PixelShader = compile ps_3_0 ps();
    }
	
    pass P1
    {
        AlphaTesTEnable = TRUE;
        AlphaBlendEnable = TRUE;
        ZWriteEnable = TRUE;
        ZEnable = TRUE;
        CullMode = CCW;
        ShadeMode = GOURAUD;

        VertexShader = compile vs_3_0 vs();
        PixelShader = compile ps_3_0 Texps();
    }
}