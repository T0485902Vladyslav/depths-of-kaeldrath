#include "ItemScene.h"
#include <iostream>
using namespace std;

ItemScene::ItemScene(int c_index, string c_description,
      string c_choice_A,      string c_choice_B,
      string c_consequence_A, string c_consequence_B,
      int c_next_scene_A,      int c_next_scene_B,
      Item c_item_A,          Item c_item_B)
: Scene(c_index, c_description,
        c_choice_A, c_choice_B,
        c_consequence_A, c_consequence_B,
        c_next_scene_A, c_next_scene_B),
        item_A(c_item_A), item_B(c_item_B) {}

int ItemScene::play(Player& player) {
    cout << "\n" << description << endl;
    int next = presentChoices(player);

    if (last_choice == 'A') {
        player.addItem(item_A);
    } else {
        player.addItem(item_B);
    }

    return next;
}