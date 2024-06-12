#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//�n�ʃ��f���N���X
class Stage_Floor : public StageBase
{
    int hModel_;    //���f���ԍ�

public:
    Stage_Floor(GameObject* parent);
    ~Stage_Floor();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    // ���f���ԍ��擾�p
    int GetModelHandle() const { return hModel_; }
};