#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//�n�ʃ��f���N���X
class Stage : public StageBase
{
    int hModel_;    //���f���ԍ�

public:
    Stage(GameObject* parent);
    ~Stage();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // ���f���ԍ��擾�p
    int GetModelHandle() const { return hModel_; }
};