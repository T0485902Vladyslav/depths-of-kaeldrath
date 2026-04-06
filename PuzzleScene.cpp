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

// If player chose A: ask the question, check answer and reward or punish
// If player chose B: skip puzzle and take damage
int PuzzleScene::play(Player& player) {
    cout << "\n" << description << endl;

    int next = presentChoices(player);

    if (next == next_scene_id_A) {
        cout << "\n" << question << endl;
        cout << "\n" << player.getName() << ", you must answer to proceed." << endl;

        string user_answer;
        bool valid_input = false;

        while (!valid_input) {
            cout << "Your answer: ";
            getline(cin, user_answer);

            //Method to trim whitespace from user input
            user_answer.erase(0, user_answer.find_first_not_of(' '));
            user_answer.erase(user_answer.find_last_not_of(' ') + 1);

            if (user_answer.empty()) {
                cout << "Answer cannot be empty. Try again.\n";
            } else {
                valid_input = true;
            }
        }

        // Convert both to lowercase for proper comparison
        for (char & i : answer) {
            i = tolower(i);
        }
        for (char & i : user_answer) {
            i = tolower(i);
        }

        if (user_answer == answer) {
            cout << "\n>> Correct! Well done, " << player.getName() << endl;
            player.addScore(score_reward);
            cout << "Your score has increased by " << score_reward << endl;
        } else {
            cout << "Wrong! The answer was: " << answer << endl;
            if (damage_on_fail > 0) {
                player.takeDamage(damage_on_fail);
                cout << "You take " << damage_on_fail << " damage!" << endl;
            }
        }
    } else {
        if (damage_on_fail > 0) {
            player.takeDamage(damage_on_fail);
            cout << "You take " << damage_on_fail << " damage!" << endl;
        }
    }

    return next;
}