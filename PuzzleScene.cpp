#include "PuzzleScene.h"
#include <iostream>
using namespace std;

PuzzleScene::PuzzleScene(int c_index, const string& c_description,
    const string& c_choice_A, const string& c_choice_B,
    const string& c_consequence_A, const string& c_consequence_B,
    int c_next_scene_A, int c_next_scene_B,
    const string& c_question, const string& c_answer,
    int c_score_reward, int c_damage_on_fail)
: Scene(c_index, c_description,
    c_choice_A, c_choice_B,
    c_consequence_A, c_consequence_B,
    c_next_scene_A, c_next_scene_B) {
    question = c_question;
    answer = c_answer;
    score_reward = c_score_reward;
    damage_on_fail = c_damage_on_fail;
    }

int PuzzleScene::play(Player& player) {
    cout << "\n" << description << endl;

    int next = presentChoices(player);

    if (next == next_scene_id_A) {
        cout << "\n" << question << endl;
        cout << "\n" << player.getName() << ", you must answer to proceed." << endl;

        string userAnswer;
        bool validInput = false;

        while (!validInput) {
            cout << "Your answer: ";
            getline(cin, userAnswer);

            if (userAnswer.empty()) {
                cout << "Answer cannot be empty. Try again.\n";
            } else {
                validInput = true;
            }
        }

        for (int i = 0; i < (int)answer.size(); i++) {
            answer[i] = tolower(answer[i]);
        }
        for (int i = 0; i < (int)userAnswer.size(); i++) {
            userAnswer[i] = tolower(userAnswer[i]);
        }

        if (userAnswer == answer) {
            cout << "\n>> Correct! Well done, " << player.getName() << endl;
            player.addScore(score_reward);
            cout << "Your score has increased by " << score_reward << endl;
        } else {
            cout << "Wrong! The answer was: " << answer << endl;
            player.takeDamage(damage_on_fail);
            cout << "You take " << damage_on_fail << " damage for wrong answer!" << endl;
        }
    } else {
        player.takeDamage(damage_on_fail);
        cout << "You take " << damage_on_fail << " damage!" << endl;
    }

    return next;
}