#pragma once
#include "Scene.h"
#include "Enemy.h"

class CombatScene : public Scene {
private:
    Enemy enemy;

    void runCombat(Player& player);
public:
    CombatScene(int c_index, string c_description, string c_choice_A, string c_choice_B,
        string c_consequence_A, string c_consequence_B, int c_next_scene_A, int c_next_scene_B, Enemy c_enemy);

    int play(Player& player) override;
};