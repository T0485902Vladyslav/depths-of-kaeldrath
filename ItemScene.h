#pragma once
#include "Scene.h"
#include "Item.h"

class ItemScene : public Scene {
private:
    Item item_A;
    Item item_B;
public:
    ItemScene(int c_index, string c_description,
          string c_choice_A,      string c_choice_B,
          string c_consequence_A, string c_consequence_B,
          int c_next_scene_A,      int c_next_scene_B,
          Item c_item_A,          Item c_item_B);

    int play(Player& player) override;
};