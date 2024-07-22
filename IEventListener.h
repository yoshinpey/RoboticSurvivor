#pragma once

class GameEvent;

// イベントリスナーのインターフェース
class IEventListener
{
public:
    virtual ~IEventListener() = default;
    virtual void OnEvent(const GameEvent& event) = 0;
};
