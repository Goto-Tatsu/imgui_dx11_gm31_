Texture2D Texture0 : register(t0);
Texture2D Texture1 : register(t1);
Texture2D Texture2 : register(t2);
//Texture2D Textures[2] : register(t0);

SamplerState Sampler : register(s0);

struct PS_IN
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION0;
    float3 binormalW : BINORMAL0;
    float3 tangentW : TANGENT0;
    float3 normalW : NORMAL0;
    float2 texcoord : TEXCOORD0;
};

cbuffer ConstantBuffer : register(b0)
{
    float4 mtxWVP;
    float4 mtxWIT;
    float4 mtxWorld;
    float4 cameraPos;
}


float4 main(PS_IN input) : SV_TARGET
{
    float4 normalmap = Texture1.Sample(Sampler, input.texcoord) * 2.0f - 1.0f;
    
    // ������xyz�͖ڂŌ���+-���߂��Ă����Ă��������B
    float3 normalW = normalize(-input.binormalW * normalmap.x + input.tangentW * normalmap.y + input.normalW * normalmap.z);
    
    float3 lightDirW = float3(1.0f, -1.0f, 1.0f); /// �{���̓��W�X�^(CPU)���瑗���Ă����Ă���

	// ���s���̖��邳
    lightDirW = normalize(lightDirW);
    
    float l = saturate(dot(-lightDirW, input.normalW));
    
	//// �X�y�L�����[ ////
    float3 refW = reflect(lightDirW, normalW); // ���C�g�x�N�g��
    float3 eyeW = cameraPos.xyz - input.posW; // �����x�N�g��
    refW = normalize(refW); // �m�[�}���C�Y
    eyeW = normalize(eyeW); // �m�[�}���C�Y
    
    // �����}�b�s���O ///////////////////////////
    //float3 eyeT;    // ������normalW�ƍ��킹�Ă�
    //eyeT.x = dot(eyeW, -input.binormalW);
    //eyeT.y = dot(eyeW, input.tangentW);
    //eyeT.z = dot(eyeW, input.normalW);
    //float height_map = Texture[1].Sample(Sampler, input.texcoord) * 2.0f - 1.0f;
    //float2 parallax_texcoord = input.texcoord + (height_map * 0.2f * eyeT.xy);
    //////////////////////////////////////////////
    
    // �X�y�L�����[�ݒ�
    float s = pow(saturate(dot(refW, eyeW)), 10);
    float4 specular = float4(s, s, s, 1.0f);

    //return float4(l, l, l, 1.0f);
    return float4(Texture0.Sample(Sampler, input.texcoord).rgb * l + specular.rgb, 1.0f) + specular;

}