#pragma once
#include "Scene.h"

class LockedDoorScene : public Scene {
private:
    string key_name;
    int next_scene_no_key;
    int damage_on_fail;
public:
    LockedDoorScene(int c_index, string c_description,string c_choice_A, string c_choice_B,
                    string c_consequence_A, string c_consequence_B,int c_next_scene_A, int c_next_scene_B,
                    string c_key_name, int c_next_scene_no_key, int c_damage_on_fail);

    int play(Player& player) override;
};