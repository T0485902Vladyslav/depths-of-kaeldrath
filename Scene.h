#pragma once
#include <string>
#include "Player.h"
using namespace std;

class Scene {
protected:
    int scene_id;
    string description;
    string choice_A;
    string choice_B;
    string consequence_A;
    string consequence_B;
    int next_scene_id_A;
    int next_scene_id_B;
    char last_choice = ' ';

public:
    Scene(int c_scene_id, string c_description,
          string c_choice_A, string c_choice_B,
          string c_consequence_A, string c_consequence_B,
          int c_next_id_A, int c_next_id_B);

    virtual ~Scene() {}

    int getSceneId() const;

    virtual int play(Player& player);
    int presentChoices(Player& player);
};