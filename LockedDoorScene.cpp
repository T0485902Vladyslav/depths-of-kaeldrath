#include "LockedDoorScene.h"
#include <iostream>
using namespace std;

LockedDoorScene::LockedDoorScene(int c_index, string c_description,string c_choice_A, string c_choice_B,
                    string c_consequence_A, string c_consequence_B, int c_next_scene_A, int c_next_scene_B,
                    string c_key_name, int c_next_scene_no_key, int c_damage_on_fail)
        : Scene(c_index, c_description,c_choice_A, c_choice_B,c_consequence_A, c_consequence_B,
            c_next_scene_A, c_next_scene_B) {
    key_name = c_key_name;
    next_scene_no_key = c_next_scene_no_key;
    damage_on_fail = c_damage_on_fail;
}

int LockedDoorScene::play(Player& player) {
    cout << "\n" << description << endl;
    int next = presentChoices(player);

    if (last_choice == 'A') {
        if (player.hasKey(key_name)) {
            cout << "\nYou use the " << key_name << " to unlock the door." << endl;
            player.removeKey(key_name);
            next = next_scene_id_A;
        } else {
            cout << "\nThe door is locked. You don't have the right key." << endl;
            cout << "You try to force it open..." << endl;

            int roll = rand() % 10;
            if (roll < 2) {
                cout << "The lock breaks! You forced the door open!" << endl;
                next = next_scene_id_A;
            } else {
                cout << "The door doesn't budge. You take " << damage_on_fail << " damage!" << endl;
                player.takeDamage(damage_on_fail);
                cout << "You give up and look for another way through..." << endl;
                next = next_scene_no_key;
            }
        }
    }
    else {
        cout << "\nYou squeeze through a narrow crack in the wall." << endl;
        cout << "Loose stones fall from above and hit you. You take 10 damage!" << endl;
        player.takeDamage(10);
    }

    return next;
}