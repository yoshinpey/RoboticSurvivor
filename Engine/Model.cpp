#include "Global.h"
#include "Model.h"
#include <algorithm>

//3D���f���iFBX�t�@�C���j���Ǘ�����
namespace Model
{
	//���[�h�ς݂̃��f���f�[�^�ꗗ
	std::vector<ModelData*>	_datas;

	struct OrderModel
	{
		int handle_;
		int drawOrder_;		//�`�悷�鏇��
		int shadeType_;		//�V�F�[�_�[�̃^�C�v
		bool isDraw_;		//�`�悷�邩�ǂ���
	};
	std::vector <OrderModel*> _orderDatas;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//���f�������[�h
	int Load(std::string fileName, int _order, int _type)
	{
		ModelData* pData = new ModelData;

		//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pFbx = _datas[i]->pFbx;
				isExist = true;
				break;
			}
		}

		//�V���Ƀt�@�C�����J��
		if (isExist == false)
		{
			pData->pFbx = new Fbx;
			if (FAILED(pData->pFbx->Load(fileName)))
			{
				//�J���Ȃ�����
				SAFE_DELETE(pData->pFbx);
				SAFE_DELETE(pData);
				return -1;
			}

			//�����J����
			pData->fileName = fileName;
		}

		//�g���ĂȂ��ԍ����������T��
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;

				if (_order >= 0) {
					OrderModel* pOr = new OrderModel;
					pOr->handle_ = (int)_datas.size() - 1;
					pOr->drawOrder_ = _order;
					pOr->shadeType_ = _type;
					pOr->isDraw_ = true;
					_orderDatas.push_back(pOr);

					// �`�揇���Ɋ�Â��ă\�[�g
					std::sort(_orderDatas.begin(), _orderDatas.end(),
						[](const OrderModel* a, const OrderModel* b) {
							return a->drawOrder_ < b->drawOrder_;
						});
				}

				return i;
			}
		}

		//�V���ɒǉ�
		_datas.push_back(pData);

		if (_order >= 0) {
			OrderModel* pOr = new OrderModel;
			pOr->handle_ = (int)_datas.size() - 1;
			pOr->drawOrder_ = _order;
			pOr->shadeType_ = _type;
			pOr->isDraw_ = true;
			_orderDatas.push_back(pOr);

			// �`�揇���Ɋ�Â��ă\�[�g
			std::sort(_orderDatas.begin(), _orderDatas.end(),
				[](const OrderModel* a, const OrderModel* b) {
					return a->drawOrder_ < b->drawOrder_;
				});
		}

		return (int)_datas.size() - 1;
	}

	//�`��
	void Draw(int handle, int type)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//�A�j���[�V������i�߂�
		if (_datas[handle]->isAimeStop == false) _datas[handle]->nowFrame += _datas[handle]->animSpeed;

		//�Ō�܂ŃA�j���[�V����������߂�
		if (_datas[handle]->nowFrame > (float)_datas[handle]->endFrame)
			_datas[handle]->nowFrame = (float)_datas[handle]->startFrame;

		/* Blend
		if (e->isBlending) {
			//�A�j���[�V������i�߂�
			e->blendNowFrame += e->animSpeed;

			//�Ō�܂ŃA�j���[�V����������߂�
			if (e->blendNowFrame > (float)e->blendEndFrame)
				e->blendNowFrame = (float)e->blendStartFrame;

			e->pFbx->Draw(e->transform, (int)e->nowFrame,
				(int)e->blendNowFrame, (float)e->blendWeight);

			return;
		}
		*/

		if (_datas[handle]->pFbx)
		{
			// ���݂̃A�j���[�V�����t���[���Ń��f����`��
			_datas[handle]->pFbx->Draw(_datas[handle]->transform, (int)_datas[handle]->nowFrame, type);

		}
	}

	void DrawOrder()
	{
		for (OrderModel* e : _orderDatas) {
			if (!e->isDraw_ || e->drawOrder_ != 0 || e == nullptr) continue;

			//�A�j���[�V������i�߂�
			if (_datas[e->handle_]->isAimeStop == false) _datas[e->handle_]->nowFrame += _datas[e->handle_]->animSpeed;

			//�Ō�܂ŃA�j���[�V����������߂�
			if (_datas[e->handle_]->nowFrame > (float)_datas[e->handle_]->endFrame)
				_datas[e->handle_]->nowFrame = (float)_datas[e->handle_]->startFrame;

			if (_datas[e->handle_]->pFbx)
			{
				// ���݂̃A�j���[�V�����t���[���Ń��f����`��
				_datas[e->handle_]->pFbx->Draw(_datas[e->handle_]->transform, (int)_datas[e->handle_]->nowFrame, e->shadeType_);
			}
		}

		for (OrderModel* e : _orderDatas) {
			if (!e->isDraw_ || e->drawOrder_ != 1 || e == nullptr) continue;

			//�A�j���[�V������i�߂�
			if (_datas[e->handle_]->isAimeStop == false) _datas[e->handle_]->nowFrame += _datas[e->handle_]->animSpeed;

			//�Ō�܂ŃA�j���[�V����������߂�
			if (_datas[e->handle_]->nowFrame > (float)_datas[e->handle_]->endFrame)
				_datas[e->handle_]->nowFrame = (float)_datas[e->handle_]->startFrame;

			if (_datas[e->handle_]->pFbx)
			{
				// ���݂̃A�j���[�V�����t���[���Ń��f����`��
				_datas[e->handle_]->pFbx->Draw(_datas[e->handle_]->transform, (int)_datas[e->handle_]->nowFrame, e->shadeType_);
			}
		}

	}


	//�C�ӂ̃��f�����J��
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//�������f���𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && i != handle && _datas[i]->pFbx == _datas[handle]->pFbx)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pFbx);
		}


		SAFE_DELETE(_datas[handle]);
	}


	//�S�Ẵ��f�������
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] != nullptr)
			{
				Release(i);
			}
		}
		_datas.clear();

		for (int i = 0; i < _orderDatas.size(); i++)
		{
			if (_orderDatas[i] != nullptr)
			{
				Release(i);
			}
		}
		_orderDatas.clear();

	}

	void SetAnimeStop(int handle, bool b)
	{
		_datas[handle]->SetAnimeStop(b);
	}

	//�A�j���[�V�����̃t���[�������Z�b�g
	void SetBlendingAnimFrame(int handle, int startFrame1, int endFrame1, int startFrame2, int endFrame2, float animSpeed, float blendWeight)
	{
		_datas[handle]->SetBlendingAnimFrame(startFrame1, endFrame1, startFrame2, endFrame2, animSpeed, blendWeight);
	}

	//�A�j���[�V�����̃t���[�������Z�b�g
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
	{
		_datas[handle]->SetAnimFrame(startFrame, endFrame, animSpeed);
	}


	//���݂̃A�j���[�V�����̃t���[�����擾
	int GetAnimFrame(int handle)
	{
		return (int)_datas[handle]->nowFrame;
	}


	//�C�ӂ̃{�[���̈ʒu���擾
	XMFLOAT3 GetBonePosition(int handle, std::string boneName)
	{
		XMFLOAT3 pos = _datas[handle]->pFbx->GetBonePosition(boneName);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _datas[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}

	XMFLOAT3 GetBoneAnimPosition(int handle, std::string boneName)
	{
		XMFLOAT3 pos = _datas[handle]->pFbx->GetBoneAnimPosition(boneName, _datas[handle]->nowFrame);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _datas[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}

	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform& transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->transform = transform;
	}


	//���[���h�s��̎擾
	XMMATRIX GetMatrix(int handle)
	{
		return _datas[handle]->transform.GetWorldMatrix();
	}


	//���C�L���X�g�i���C���΂��ē����蔻��j
	void RayCast(int handle, RayCastData* data)
	{
		XMFLOAT3 target = Transform::Float3Add(data->start, data->dir);
		XMMATRIX matInv = XMMatrixInverse(nullptr, _datas[handle]->transform.GetWorldMatrix());
		XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
		XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
		XMVECTOR vecDir = vecTarget - vecStart;

		XMStoreFloat3(&data->start, vecStart);
		XMStoreFloat3(&data->dir, vecDir);

		_datas[handle]->pFbx->RayCast(data);
	}

	void StopDraw(int handle)
	{
		for (auto it = _orderDatas.begin(); it != _orderDatas.end(); ++it)
		{
			if ((*it)->handle_ == handle)
			{
				delete* it;
				_orderDatas.erase(it);
				break;
			}
		}
	}
}