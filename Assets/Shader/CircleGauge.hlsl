//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D g_texture : register(t0); // テクスチャー
SamplerState g_sampler : register(s0); // テクスチャーサンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
    matrix g_matWorld; // 頂点座標変換行列
    matrix g_matTexture; // テクスチャ座標変換行列
    float4 g_vecColor; // テクスチャ合成
    float2 g_angle;
    float  start;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUTPUT
{
    float4 pos : SV_POSITION; // 位置
    float2 uv : TEXCOORD; // UV座標
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUTPUT VS(float4 pos : POSITION, float4 uv : TEXCOORD)
{
    VS_OUTPUT output;
    output.pos = mul(pos, g_matWorld);
    output.uv = mul(uv, g_matTexture);
    return output;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUTPUT input) : SV_Target
{  
    float2 uvpos = float2(2.0 * input.uv.x - 1, 1.0 - 2 * input.uv.y);
    float dig = (degrees(atan2(uvpos.y, uvpos.x)) + 360 + start) % 360.0;
    if (g_angle.x < g_angle.y)
    {
   
        if (dig > g_angle.x && dig < g_angle.y)
        {
            return g_vecColor * g_texture.Sample(g_sampler, input.uv);
        }
        else
            return (0, 0, 0, 0);
    }
    else if (g_angle.x > g_angle.y)
    {
        if (dig < g_angle.x && dig > g_angle.y)
        {
           return (0, 0, 0, 0);
        }
        else
           return g_vecColor * g_texture.Sample(g_sampler, input.uv);
    }else
    {
        return (0, 0, 0, 0);
    }
}