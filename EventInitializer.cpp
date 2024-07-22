#include "EventInitializer.h"
#include "EventManager.h"
#include "PlayScene.h"

void EventInitializer::InitializeEvents(EventManager* eventManager, PlayScene* playScene)
{
    // 勝利条件のイベントを追加
    GameEvent victoryEvent;
    victoryEvent.state = EVENT_STATE_ACTIVE;
    victoryEvent.type = EVENT_TYPE_VICTORY;
    victoryEvent.description = "All enemies defeated";
    victoryEvent.condition = [playScene]() -> bool {
        return playScene->GetEnemyManager()->GetEnemyCount() == 0;
    };
    victoryEvent.action = [playScene]() {
        playScene->GetSceneManager()->ChangeScene(SCENE_ID_CLEAR);
    };
    eventManager->AddEvent(victoryEvent);

    // 敗北条件のイベントを追加
    GameEvent defeatEvent;
    defeatEvent.state = EVENT_STATE_ACTIVE;
    defeatEvent.type = EVENT_TYPE_DEFEAT;
    defeatEvent.description = "Player is dead";
    defeatEvent.condition = [playScene]() -> bool {
        return playScene->GetPlayer() == nullptr;
    };
    defeatEvent.action = [playScene]() {
        playScene->GetEnemyManager()->RemoveAllEnemies();
        playScene->GetSceneManager()->ChangeScene(SCENE_ID_OVER);
    };
    eventManager->AddEvent(defeatEvent);
}
