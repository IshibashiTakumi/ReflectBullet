//=============================================================================
// ライト
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
float g_lightRadius[50];
float3 g_lightPos[50];
float4 g_lightColor[50];

//=============================================================================
// 線形フォグ
//=============================================================================
float4 PointLight(float3 pos, float3 normal)
{
    //float bright;
    //float4 diffuse = float4(1, 1, 1, 1);

    //for (int count = 0; count < 50; count++)
    //{
    //    bright = 1 - min(length(pos - g_lightPos[count]) / g_lightRadius[count], 1);
    //    diffuse += lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), g_lightColor[count], bright);
    //}

    float bright;
    float3 vec;
    float4 diffuse = float4(0, 0, 0, 0);

    for (int count = 0; count < 50; count++)
    {
        vec = pos - g_lightPos[count];
        bright = (1 - min(length(vec) / g_lightRadius[count], 1)) * max(-dot(normal, normalize(vec)), 0);
        diffuse += lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), g_lightColor[count], bright);
    }

    return diffuse;

}

float4 SpotLight(float3 pos, float3 normal)
{
    float bright;
    float3 vec;
    float4 diffuse = float4(0, 0, 0, 1);

    for (int count = 0; count < 50; count++)
    {
        vec = pos - g_lightPos[count];
        if (dot(normalize(vec), float3(0, -1, 0)) > 0.8f)
        {
            bright = (1 - min(length(vec) / 700, 1));
            diffuse.rgb += g_lightColor[count].rgb * bright;
        }

    }

    return diffuse;

}