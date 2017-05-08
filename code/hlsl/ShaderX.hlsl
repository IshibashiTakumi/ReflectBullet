float4x4 g_world : WORLD;
float4x4 g_view : VIEW;
float4x4 g_proj : PROJECTION;

float3 g_CameraPos;

//float4 g_Ambient = float4(1, 1, 1, 1);
//float4 g_Diffuse = float4(1, 1, 1, 1);
//float4 g_Emissive = float4(1, 1, 1, 1);
//float g_Power = 128;
//float4 g_Specular = float4(1, 1, 1, 1);

float4 g_Ambient;
float4 g_Diffuse;
float4 g_Emissive;
float g_Power;
float4 g_Specular;

texture g_texture;
sampler g_TextureSampler =
sampler_state
{
    Texture = <g_texture>;
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

//OM_INPUT ps(PS_INPUT input)
//{
//    OM_INPUT output = (OM_INPUT) 0;

//    float3 normal = normalize(input.normal.xyz);

//    output.color = float4(0.2f, 0.2f, 0.3f, 1.0f);

//    //for (int count = 0; count < 10; count++)
//    //{
//    //    float bright = 1 - min(length(input.positionW.xyz - g_lightPos[count]) / g_lightRadius[count], 1);
//    //    float4 brightColor = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), g_lightColor[count], bright);

//    //    output.color += brightColor;
//    //}

//    output.color *= input.color;

//    return output;
//}

OM4_INPUT Texps(PS_INPUT input)
{
    OM4_INPUT output = (OM4_INPUT) 0;
    
    //float col = input.depth.z / input.depth.w;
    ////output.color0 = float4(col, col, col, 1);

    //float4 unpacked_depth = float4(0, 0, 256.0f, 256.0f);
    //unpacked_depth.g = modf(col * 256.0f, unpacked_depth.r);
    //unpacked_depth.b *= modf(unpacked_depth.g * 256.0f, unpacked_depth.g);

    //output.color0 = unpacked_depth / 256.0f; // 標準化

    output.color0 = input.positionW;

    output.color1 = (input.normal + 1.0f) * 0.5f;
    output.color2 = input.color * g_Diffuse * tex2D(g_TextureSampler, input.tex);

    float3 Vec = float3(-1.0f, 1.0f, 0.5f);
    float3 HVec = normalize(Vec + normalize(g_CameraPos - input.positionW.xyz)); // ハーフベクトル
	
    float Specular = pow(max(0, dot(normalize((output.color1.xyz * 2.0f) - 1.0f), HVec)), g_Power); // 鏡面反射光

    output.color3 = float4(g_Specular.rgb * Specular, g_Specular.a);
    
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
        CullMode = CCW;
        ShadeMode = GOURAUD;

        VertexShader = compile vs_3_0 vs();
        PixelShader = compile ps_3_0 Texps();
    }
	
    pass P1
    {
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
}