#include "Utility.hlsl"

float g_Criteria = 0;

float g_Seed = 0.0f;
float g_Amplitude = 0.0f;
float g_Tile = 5.0f;

texture g_Texture;
sampler g_TextureSampler =
sampler_state
{
    Texture = <g_Texture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_Mask;
sampler g_MaskSampler =
sampler_state
{
    Texture = <g_Mask>;
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

float2 Noise(float2 TexCoord)
{

    TexCoord.x += g_Amplitude * (hash(float2(ceil(TexCoord.y * g_Tile) / g_Tile, g_Seed)) - 0.5);
    TexCoord.x += 0.5 * g_Amplitude * (hash(float2(ceil(TexCoord.y * 1.761 * g_Tile) / (1.761 * g_Tile), g_Seed)) - 0.5);
    TexCoord.x += 0.25 * g_Amplitude * (hash(float2(ceil(TexCoord.y * 3.1781 * g_Tile) / (3.1781 * g_Tile), g_Seed)) - 0.5);
				
    TexCoord.y += g_Amplitude * (hash(float2(ceil(TexCoord.y * g_Tile) / g_Tile, g_Seed)) - 0.5);

    return TexCoord.xy;
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
    output.color = input.color * tex2D(g_TextureSampler, Noise(input.tex));

    return output;
}

OM_INPUT TexpsAlpha(PS_INPUT input)
{
    OM_INPUT output = (OM_INPUT) 0;

    float alpha = tex2D(g_MaskSampler, input.tex).rgb / float3(1.0f, 1.0f, 1.0f);
    if (alpha > g_Criteria)
        alpha = 1.0f;
    else
        alpha = 0.0f;

    output.color = input.color * tex2D(g_TextureSampler, input.tex);
    output.color.a = alpha;

    return output;
}

technique T0
{
    pass P0
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

    pass P1
    {
        AlphaTesTEnable = TRUE;
        AlphaBlendEnable = TRUE;
        ZWriteEnable = TRUE;
        ZEnable = TRUE;
        CullMode = CCW;
        ShadeMode = GOURAUD;

        VertexShader = compile vs_3_0 vs();
        PixelShader = compile ps_3_0 TexpsAlpha();
    }

    pass P2
    {
        AlphaTesTEnable = TRUE;
        AlphaBlendEnable = TRUE;
        ZEnable = TRUE;
        CullMode = CCW;
        ShadeMode = GOURAUD;

        VertexShader = compile vs_3_0 vs();
        PixelShader = compile ps_3_0 ps();
    }
}