#pragma once

class EventManager;
class PlayScene;

class EventInitializer
{
public:
    static void InitializeEvents(EventManager* eventManager, PlayScene* playScene);
};

