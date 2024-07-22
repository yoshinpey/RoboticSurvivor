#pragma once
#include <string>
#include <functional>

enum EVENT_TYPE {
    EVENT_TYPE_ENEMY_DEFEATED,
    EVENT_TYPE_PLAYER_DAMAGED,
    EVENT_TYPE_GAME_WIN,
    EVENT_TYPE_GAME_OVER,
};

enum EVENT_STATE {
    EVENT_STATE_INACTIVE,
    EVENT_STATE_ACTIVE,
    EVENT_STATE_COMPLETED,
};

// イベントに関する構造体と関連する定数の定義
struct GameEvent {
    EVENT_TYPE type;
    EVENT_STATE state;
    std::string description;
};
