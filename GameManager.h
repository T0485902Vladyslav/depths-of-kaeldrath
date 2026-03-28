#pragma once
#include <vector>
#include "Scene.h"
#include "Player.h"
#include "SaveManager.h"
using namespace std;

class GameManager {
private:
    vector<Scene*> scenes;
    Player player;
    int current_scene_ID;
    SaveManager save_manager;

    void setupScenes();
    void showMainMenu();
public:
    GameManager();
    ~GameManager();

    void setupPlayer();
    void gameLoop();
    void run();
};