#pragma once
#include "Scene.h"

class PuzzleScene : public Scene {
private:
    string question;
    string answer;
    int score_reward;
    int damage_on_fail;
public:
    PuzzleScene(int c_index, const string& c_description,
        const string& c_choice_A, const string& c_choice_B,
        const string& c_consequence_A, const string& c_consequence_B,
        int c_next_scene_A, int c_next_scene_B,
        const string& c_question, const string& c_answer,
        int c_score_reward, int c_damage_on_fail);

    int play(Player& player) override;
};