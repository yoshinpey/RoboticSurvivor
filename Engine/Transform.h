#pragma once
#include <DirectXMath.h>

using namespace DirectX;


//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	Transform * pParent_;	//�e�I�u�W�F�N�g�̏��

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();


	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
};

//�ǉ�����
inline XMFLOAT3 operator += (XMFLOAT3& p, const XMVECTOR& v) {
	XMVECTOR pv = XMLoadFloat3(&p);
	pv += v;
	XMStoreFloat3(&p, pv);
	return p;
}

inline XMFLOAT3 operator + (const XMFLOAT3& v1, const XMVECTOR& v2) {
	XMVECTOR pv = XMLoadFloat3(&v1);
	pv += v2;
	XMFLOAT3 out;
	XMStoreFloat3(&out, pv);
	return out;
}

inline float Length(XMVECTOR v) {
	XMVECTOR lenVec = XMVector3Length(v);
	return XMVectorGetX(lenVec);
}

inline XMVECTOR operator - (const XMFLOAT3& p1, const XMFLOAT3& p2) {
	XMVECTOR p1v = XMLoadFloat3(&p1);
	XMVECTOR p2v = XMLoadFloat3(&p2);
	return p1v - p2v;
}
