#pragma once
#include <vector>
#include "Scene.h"
#include "Player.h"
using namespace std;

class GameManager {
private:
    vector<Scene*> scenes;
    Player player;
    int current_scene_ID;

    void setupScenes();
    static void showMainMenu();
public:
    GameManager();
    ~GameManager();

    void setupPlayer();
    void gameLoop();
    void run();
};