float4x4 g_world : WORLD;
float4x4 g_view : VIEW;
float4x4 g_proj : PROJECTION;
float3 g_CameraPos;
float3 g_lightVec[3];
float4 g_color[3];
float g_Criteria = 0;
float g_texmove = 0.0f;

texture g_texture;
sampler g_sampler =
sampler_state
{
    Texture = <g_texture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_NormalTex;
sampler g_NormalSampler =
sampler_state
{
    Texture = <g_NormalTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_MaskTex;
sampler g_MaskSampler =
sampler_state
{
    Texture = <g_MaskTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture g_SpecularTex;
sampler g_SpecularSampler =
sampler_state
{
    Texture = <g_SpecularTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

struct VS_INPUT
{
    float4 position : POSITION;
    float4 normal : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 color : COLOR0;
};

struct PS_INPUT
{
    float4 position : POSITION;
    float4 normal : NORMAL0;
    float2 tex : TEXCOORD0;
    float4 positionW : TEXCOORD1;
    float4 color : COLOR0;
};

struct OM_INPUT
{
    float4 color : COLOR0;
};

struct OM4_INPUT
{
    float4 color0 : COLOR0;
    float4 color1 : COLOR1;
    float4 color2 : COLOR2;
    float4 color3 : COLOR3;
};

PS_INPUT vs(VS_INPUT input)
{
    PS_INPUT output;

    output.position = mul(mul(mul(input.position, g_world), g_view), g_proj);

    float4x4 nrmWorld = g_world;
    nrmWorld[3] = float4(0, 0, 0, 1);

    output.normal = mul(input.normal, nrmWorld);

    output.tex = input.tex;

    output.color = input.color;

    output.positionW = mul(input.position, g_world);

    return output;
}

OM_INPUT ps(PS_INPUT input)
{
    OM_INPUT output = (OM_INPUT) 0;

    float3 normal = normalize(input.normal.xyz);

    output.color = float4(0.2f, 0.2f, 0.3f, 1.0f);

    //for (int count = 0; count < 10; count++)
    //{
    //    float bright = 1 - min(length(input.positionW.xyz - g_lightPos[count]) / g_lightRadius[count], 1);
    //    float4 brightColor = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), g_lightColor[count], bright);

    //    output.color += brightColor;
    //}

    output.color *= input.color;

    return output;
}

OM_INPUT Texps(PS_INPUT input)
{
    OM_INPUT output = (OM_INPUT) 0;

    float3 normal = normalize(input.normal.xyz);
    float bright;
    float4 shadow, diffuse, brightColor;
    int count;
    for (count = 0; count < 3; count++)
    {
        bright = max(-dot(normal, g_lightVec[count]), 0);

        shadow = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), g_color[count], bright);

        diffuse = tex2D(g_sampler, input.tex) * shadow;

        output.color += diffuse;
    }

    output.color /= 3;

    //for (count = 0; count < 10; count++)
    //{
    //    float bright = 1 - min(length(input.positionW.xyz - g_lightPos[count]) / g_lightRadius[count], 1);
    //    float4 texcolor = tex2D(g_sampler, input.tex) * g_lightColor[count];
    //    float4 brightColor = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), texcolor, bright);

    //    output.color += brightColor;
    //}

    return output;
}


PS_INPUT vs0(VS_INPUT input)
{
    PS_INPUT output;

    output.position = mul(mul(mul(input.position, g_world), g_view), g_proj);

    float4x4 nrmWorld = g_world;
    nrmWorld[3] = float4(0, 0, 0, 1);

    output.normal = mul(input.normal, nrmWorld);

    output.tex = input.tex;

    output.color = input.color;
    
    output.positionW = mul(input.position, g_world);

    return output;
}

OM4_INPUT Texps0(PS_INPUT input)
{
    OM4_INPUT output = (OM4_INPUT) 0;
    
    //float col = input.depth.z / input.depth.w;
    ////output.color0 = float4(col, col, col, 1);

    //float4 unpacked_depth = float4(0, 0, 256.0f, 256.0f);
    //unpacked_depth.g = modf(col * 256.0f, unpacked_depth.r);
    //unpacked_depth.b *= modf(unpacked_depth.g * 256.0f, unpacked_depth.g);

    //output.color0 = unpacked_depth / 256.0f; // 標準化

    output.color2 = input.color * tex2D(g_sampler, input.tex);
    if (output.color2.a == 0) discard;

    output.color0 = input.positionW;

    //float4 nor = tex2D(g_NormalSampler, input.tex + float2(g_texmove, 0)) * tex2D(g_NormalSampler, input.tex + float2(0, g_texmove));
    //output.color1 = (((input.normal * nor) + 1.0f) * 0.5f);
    //output.color1 = (((input.normal * tex2D(g_NormalSampler, input.tex))+ 1.0f) * 0.5f);
    output.color1 = ((input.normal + 1.0f) * 0.5f) * ((tex2D(g_NormalSampler, input.tex) + 1.0f) * 0.5f);

    float3 Vec = -g_lightVec[0].xyz;
    float3 HVec = normalize(Vec + normalize(g_CameraPos - input.positionW.xyz)); // ハーフベクトル
	
    float Specular = pow(max(0, dot(normalize((output.color1.xyz * 2.0f) - 1.0f), HVec)), 128); // 鏡面反射光

    float3 color = tex2D(g_SpecularSampler, input.tex + float2(g_texmove, 0)).rgb * tex2D(g_SpecularSampler, input.tex + float2(0, g_texmove)).rgb;
    output.color3 = float4(color + Specular, 1);
    //output.color3 = float4(Specular, Specular, Specular, 1);
    
    
    return output;
}

OM4_INPUT MaskTexps0(PS_INPUT input)
{
    OM4_INPUT output = (OM4_INPUT) 0;
    
    //float col = input.depth.z / input.depth.w;
    ////output.color0 = float4(col, col, col, 1);

    //float4 unpacked_depth = float4(0, 0, 256.0f, 256.0f);
    //unpacked_depth.g = modf(col * 256.0f, unpacked_depth.r);
    //unpacked_depth.b *= modf(unpacked_depth.g * 256.0f, unpacked_depth.g);

    //output.color0 = unpacked_depth / 256.0f; // 標準化

    float criteria = tex2D(g_MaskSampler, input.tex).rgb / float3(1.0f, 1.0f, 1.0f);
    if (criteria < g_Criteria) input.color = float4(0.2, 0.2, 0.2, 1);
        
    output.color2 = input.color * tex2D(g_sampler, input.tex);
    if (output.color2.a == 0)
        discard;

    output.color0 = input.positionW;

    //float4 nor = tex2D(g_NormalSampler, input.tex + float2(g_texmove, 0)) * tex2D(g_NormalSampler, input.tex + float2(0, g_texmove));
    //output.color1 = (((input.normal * nor) + 1.0f) * 0.5f);
    //output.color1 = (((input.normal * tex2D(g_NormalSampler, input.tex))+ 1.0f) * 0.5f);
    output.color1 = ((input.normal + 1.0f) * 0.5f) * ((tex2D(g_NormalSampler, input.tex) + 1.0f) * 0.5f);

    float3 Vec = -g_lightVec[0].xyz;
    float3 HVec = normalize(Vec + normalize(g_CameraPos - input.positionW.xyz)); // ハーフベクトル
	
    float Specular = pow(max(0, dot(normalize((output.color1.xyz * 2.0f) - 1.0f), HVec)), 128); // 鏡面反射光

    float3 color = tex2D(g_SpecularSampler, input.tex + float2(g_texmove, 0)).rgb * tex2D(g_SpecularSampler, input.tex + float2(0, g_texmove)).rgb;
    output.color3 = float4(color + Specular, 1);
    //output.color3 = float4(Specular, Specular, Specular, 1);
    
    
    return output;
}

/////影描画用/////
float4x4 g_LightView : VIEW;
float4x4 g_LightProj : PROJECTION;

struct SVS_INPUT
{
    float4 position : POSITION;
};

struct SPS_INPUT
{
    float4 position : POSITION;
    float4 positionW : TEXCOORD0;
};

struct SOM_INPUT
{
    float4 color : COLOR0;
};

SPS_INPUT Svs(SVS_INPUT input)
{
    SPS_INPUT output;

    output.position = mul(mul(mul(input.position, g_world), g_LightView), g_LightProj);
    output.positionW = output.position;

    return output;
}

SOM_INPUT Sps(SPS_INPUT input)
{
    SOM_INPUT output = (SOM_INPUT) 0;

    float col = input.positionW.z / input.positionW.w;

    float4 unpacked_depth = float4(0, 0, 256.0f, 256.0f);
    unpacked_depth.g = modf(col * 256.0f, unpacked_depth.r);
    unpacked_depth.b *= modf(unpacked_depth.g * 256.0f, unpacked_depth.g);

    output.color = unpacked_depth / 256.0f; // 標準化

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

        VertexShader = compile vs_3_0 vs0();
        PixelShader = compile ps_3_0 Texps0();
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

    pass P2
    {
        CullMode = CCW;
        ShadeMode = GOURAUD;
        VertexShader = compile vs_3_0 Svs();
        PixelShader = compile ps_3_0 Sps();
    }

    pass P3
    {
        AlphaTesTEnable = TRUE;
        AlphaBlendEnable = TRUE;
        ZWriteEnable = TRUE;
        ZEnable = TRUE;
        CullMode = CCW;
        ShadeMode = GOURAUD;

        VertexShader = compile vs_3_0 vs();
        PixelShader = compile ps_3_0 MaskTexps0();
    }
}