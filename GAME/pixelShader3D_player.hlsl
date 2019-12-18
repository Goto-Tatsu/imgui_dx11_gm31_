Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    float4 mtxWVP;
    float4 mtxWIT;
    float4 mtxWorld;
    float4 cameraPos;
}

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 normal : NORMAL0;
    float4 color : COLOR0;
    float2 texcoord : TEXCOORD0;

    float3 posW : POSITION1;
    float3 normalW : NORMAL1;

};

float4 main(PS_IN input) : SV_TARGET
{
	//// 2019/11/25 ���C�g�x�N�g��(��)���ł��������� ////
    float3 lightDir = (1.0f, -1.0f, 1.0f); /// �{���̓��W�X�^(CPU)���瑗���Ă����Ă���
	//float light = dot(-normalize(lightDir), input.normalW);
	//light = saturate(light);

    // �n�[�t�����o�[�g
    float light = (dot(-normalize(lightDir), input.normalW) + 1.0f) * 0.5f;
	/////////////////////////////////////////////////

	/* �X�y�L�����[�v�Z */
    float4 posWorld = mul(input.posW, mtxWorld); // ���̂�World���W
    float3 refv = reflect(lightDir, input.normalW); // ���C�g�x�N�g��
    float3 eyev = posWorld.xyz - cameraPos.xyz; // �����x�N�g��
    refv = normalize(refv); // �m�[�}���C�Y
    eyev = normalize(eyev); // �m�[�}���C�Y
    float s = dot(refv, eyev); // �X�y�L�����[�ݒ�
    s = saturate(s);
    s = pow(s, 10);
    float4 specular = float4(s, s, s, 1.0f);

    return float4(g_Texture.Sample(g_Sampler, input.texcoord).rgb * light + specular.rgb, 1.0f) + specular;
	//return g_Texture.Sample(g_Sampler, input.texcoord) * light + specular;
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}