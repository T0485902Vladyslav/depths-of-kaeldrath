#include "Scene.h"
#include <iostream>
using namespace std;

Scene::Scene(int c_scene_id, string ccene_description, string c_choice_A,
        string c_choice_B, string c_consequence_A, string c_consequence_B, int c_next_id_A, int c_next_id_B) {

    scene_id = c_scene_id;
    description = ccene_description;
    choice_A = c_choice_A;
    choice_B = c_choice_B;
    consequence_A = c_consequence_A;
    consequence_B = c_consequence_B;
    next_scene_id_A = c_next_id_A;
    next_scene_id_B = c_next_id_B;

}

int Scene::getSceneId() const {
    return scene_id;
}

int Scene::play(Player& player) {
    cout << "\n" << description << endl;
    return presentChoices(player);
}

int Scene::presentChoices(Player& player) {
    cout << "\nA) " << choice_A << endl;
    cout << "B) " << choice_B << endl;
    cout << "----------------------------------------------" << endl;

    char userChoice = ' ';
    bool valid_input = false;

    while (!valid_input) {
        cout << player.getName() << ", what do you do? (A/B): ";

        string line;
        getline(cin, line);

        if (line.empty()) {
            cout << "Input cannot be empty. Please enter A or B.\n";
        } else {
            userChoice = toupper(line[0]);

            if (userChoice == 'A' || userChoice == 'B') {
                valid_input = true;
            } else {
                cout << "Invalid input. Please enter A or B.\n";
            }
        }
    }

    last_choice = userChoice;

    int result;
    if (userChoice == 'A') {
        cout << "\n>> " << consequence_A << endl;
        result = next_scene_id_A;
    } else {
        cout << "\n>> " << consequence_B << endl;
        result = next_scene_id_B;
    }

    return result;
}