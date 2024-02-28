//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D g_texture : register(t0); //�e�N�X�`���[
SamplerState g_sampler : register(s0); //�T���v���[

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
    float4x4 g_matWVP; // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
    float4x4 g_matNormalTrans; // �@���̕ϊ��s��i��]�s��Ɗg��̋t�s��j
    float4x4 g_matWorld; // ���[���h�ϊ��s��
    float4 g_vecLightDir; // ���C�g�̕����x�N�g��
    float4 g_vecDiffuse; // �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
    float4 g_vecAmbient; // �A���r�G���g�J���[�i�e�̐F�j
    float4 g_vecSpeculer; // �X�y�L�����[�J���[�i�n�C���C�g�̐F�j
    float4 g_vecCameraPosition; // ���_�i�J�����̈ʒu�j
    float g_shuniness; // �n�C���C�g�̋����i�e�J����j
    bool g_isTexture; // �e�N�X�`���\���Ă��邩�ǂ���

};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
    float4 pos : SV_POSITION; //�ʒu
    float4 normal : TEXCOORD2; //�@��
    float2 uv : TEXCOORD0; //UV���W
    float4 eye : TEXCOORD1; //����
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 Normal : NORMAL, float2 Uv : TEXCOORD)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
    VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
    outData.pos = mul(pos, g_matWVP);

	//�@���̕ό`
    Normal.w = 0; //4�����ڂ͎g��Ȃ��̂�0
    Normal.x = 0;
    Normal.y = 0;
    Normal.z = 0;
    outData.normal = Normal; //������s�N�Z���V�F�[�_�[��

	//�����x�N�g���i�n�C���C�g�̌v�Z�ɕK�v
    float4 worldPos = mul(pos, g_matWorld); //���[�J�����W�Ƀ��[���h�s��������ă��[���h���W��
    outData.eye = normalize(g_vecCameraPosition - worldPos); //���_���璸�_�ʒu�������Z�����������߂ăs�N�Z���V�F�[�_�[��

	//UV�u���W
    outData.uv = Uv; //���̂܂܃s�N�Z���V�F�[�_�[��
    
    // �܂Ƃ߂ďo��
    return outData;

}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
    float4 diffuse;
    float4 ambient;

    diffuse = g_vecAmbient;
    ambient = g_vecDiffuse;
    
    return (diffuse + ambient) * 0.2;

}