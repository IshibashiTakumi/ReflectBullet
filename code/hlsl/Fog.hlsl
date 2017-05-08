//=============================================================================
// フォグ
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
float g_Start = 500.0f;
float g_End = 6000.0f;
float3 g_FogPos = float3(0, 0, 0);
float4 g_FogColor = float4(1, 1, 1, 1);

//=============================================================================
// 線形フォグ
//=============================================================================

//距離フォグ
float4 FogLinear(float3 pos)
{
    float _length = length(pos - g_FogPos);
    float fog = max(0.0f, min((_length - g_Start) / (g_End - g_Start), 1.0f));
    return lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), g_FogColor, fog);
}

//高さフォグ
float4 FogHeightLinear(float3 pos)
{
    float _length = pos.y - g_FogPos.y;
    float fog = max(0.0f, min((_length - g_Start) / (g_End - g_Start), 1.0f));
    return lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), g_FogColor, fog);
}