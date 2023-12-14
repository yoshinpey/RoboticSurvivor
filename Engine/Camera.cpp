#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//�J�����̈ʒu
	_target = XMFLOAT3(0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	if (_position.x == _target.x && _position.z == _target.z) {
		up = XMVectorSet(0, 0, 1, 0);
	}
	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), up);


	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), up);
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

// 3D���W��2D���W�ɕϊ�����
XMFLOAT3 Camera::GetScreenPosition(XMFLOAT3 pos3d)
{
	XMVECTOR v2 = XMVector3Transform(XMLoadFloat3(&pos3d), Camera::GetViewMatrix());
	v2 = XMVector3Transform(v2, Camera::GetProjectionMatrix());
	float x = XMVectorGetX(v2);
	float y = XMVectorGetY(v2);
	float z = XMVectorGetZ(v2);

	return XMFLOAT3
	(
		x / z * Direct3D::screenWidth_ / 2.0f + Direct3D::screenWidth_ / 2.0f,
		-y / z * Direct3D::screenHeight_ / 2.0f + Direct3D::screenHeight_ / 2.0f,
		0
	);
}
