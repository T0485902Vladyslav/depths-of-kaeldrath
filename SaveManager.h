#pragma once
#include <string>
#include "Player.h"
using namespace std;

class SaveManager {
private:
    string save_file;

    string itemTypeToString(ItemType type) const;
    ItemType stringToItemType(const string& str) const;
public:
    SaveManager();

    bool hasSave();
    void saveGame(Player& player, int current_scene_id) const;
    bool loadGame(Player& player, int& current_scene_id) const;
};