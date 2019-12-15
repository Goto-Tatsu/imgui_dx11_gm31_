Texture2D		Texture : register(t0);
SamplerState	Sampler : register(s0);

cbuffer ConstantBuffer:register(b0)
{
	matrix Projection;
}

struct PS_IN
{
	float4 pos		: SV_POSITION;
	float4 color	: COLOR0;
	float2 texcoord : TEXCOORD0;
};

float4 main(PS_IN input) : SV_TARGET
{
	// = (�T���v���[, UV�l)
	float4 c = Texture.Sample(Sampler, input.texcoord);
	float l = c.r * 0.299f + c.g * 0.587f + c.b * 0.114f; //��e
	//float l = c.r * 1.07f + c.g * 0.74f + c.b * 0.43f; //�Z�s�A
	//return float4(l, l, l, 1.0f) * value.r + c * (1.0f - value.r);
	// UV�m�F
	return float4(input.texcoord, 0.0f, 1.0f); 
}