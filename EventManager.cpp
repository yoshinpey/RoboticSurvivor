#include "EventManager.h"
#include "TitleScene.h"

EventManager::EventManager(GameObject* parent)
    : GameObject(parent, "EventManager")
{
}

void EventManager::Initialize()
{
    // �C�x���g�̏������������L�q
}

void EventManager::Update()
{
    // �C�x���g�̍X�V�������L�q
    UpdateEvents();
}

void EventManager::Draw()
{
    // �C�x���g�̕`�揈�����L�q
}

void EventManager::Release()
{
    // �C�x���g�̃��\�[�X����������L�q
}

void EventManager::AddEvent(const GameEvent& event)
{
    // �C�x���g�����X�g�ɒǉ�
    events.push_back(event);
}

void EventManager::UpdateEvents()
{
    // �C�x���g�̐i�s�󋵂��m�F���A�K�v�ȃA�N�V���������s
    for (size_t i = 0; i < events.size(); ++i)
    {
        if (events[i].state == EVENT_STATE_ACTIVE)
        {
            // �A�N�e�B�u�ȃC�x���g�̏��������s
            // �K�v�ɉ����ăC�x���g�̐i�s�󋵂�ύX
        }
    }
}

void EventManager::CompleteEvent(int eventIndex)
{
    // �C�x���g��������ԂɕύX
    if (eventIndex >= 0 && eventIndex < events.size())
    {
        events[eventIndex].state = EVENT_STATE_COMPLETED;
    }
}

// ���̃C�x���g�Ǘ��֘A�̃��\�b�h��ǉ�
