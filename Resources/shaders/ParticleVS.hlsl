#include "Particle.hlsli"

VSOutput main(float4 pos : POSITION, float scale : TEXCOORD)
{
    VSOutput output; // ピクセルシェーダーに渡す値
    output.pos = pos;
    output.scale = scale;
    output.color = color;
    return output;
	//output.normal = normal;
	//output.uv = uv;
}