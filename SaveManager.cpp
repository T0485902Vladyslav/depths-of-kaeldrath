#include "SaveManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

SaveManager::SaveManager() {
    save_file = "save.txt";
}

string SaveManager::itemTypeToString(ItemType type) const {
    string result = "FOOD";
    if (type == ItemType::WEAPON) {
        result = "WEAPON";
    }else if (type == ItemType::ARMOUR) {
        result = "ARMOUR";
    }else if (type == ItemType::KEY) {
        result = "KEY";
    }

    return result;
}

ItemType SaveManager::stringToItemType(const string& str) const {
    ItemType result = ItemType::FOOD;
    if (str == "WEAPON") {
        result = ItemType::WEAPON;
    }else if (str == "ARMOUR") {
        result = ItemType::ARMOUR;
    }else if (str == "KEY") {
        result = ItemType::KEY;
    }

    return result;
}

bool SaveManager::hasSave() {
    ifstream file(save_file);
    return file.good();
}

void SaveManager::saveGame(Player& player, int current_scene_id) const {
    ofstream file(save_file);

    if (!file.is_open()) {
        cout << "Error saving game." << endl;
    }else {
        file << player.getName() << "\n";
        file << player.getHealth() << "\n";
        file << player.getLives() << "\n";
        file << player.getScore() << "\n";
        file << current_scene_id << "\n";

        vector<Item> inventory = player.getInventory();
        file << inventory.size() << "\n";

        for (auto & item : inventory) {

            string name = item.getName();
            string description = item.getDescription();
            for (char& c : name) {
                if (c == ' ') {
                    c = '_';
                }
            }
            for (char& c : description) {
                if (c == ' ') {
                    c = '_';
                }
            }

            file << name << " " << itemTypeToString(item.getType()) << " "
                 << item.getEffectValue() << " " << description << " "
                 << item.getDurability() << " " << item.getMaxDurability() << "\n";
        }

        file << player.getEquippedWeaponIndex() << "\n";
        file << player.getEquippedArmourIndex() << "\n";

        file.close();
        cout << "Game successfully saved" << endl;
    }
}

bool SaveManager::loadGame(Player& player, int& current_scene_id) const {
    ifstream file(save_file);
    bool success = false;

    if (!file.is_open()) {
        cout << "Error: no save file found" << endl;
    }else {
        string name;
        int health;
        int lives;
        int score;
        int scene_id;
        int inventory_size;
        int weapon_index;
        int armour_index;

        getline(file,name);
        file >> health;
        file >> lives;
        file >> score;
        file >> scene_id;
        file >> inventory_size;

        vector<Item> inventory;

        for (int i = 0; i < inventory_size; i++) {
            string item_name;
            string type_str;
            string item_description;
            int effect;
            int durability;
            int max_durability;

            file >> item_name;
            file >> type_str;
            file >> effect;
            file >> item_description;
            file >> durability;
            file >> max_durability;

            for (char& c : item_name) {
                if (c == '_') {
                    c = ' ';
                }
            }

            for (char& c : item_description) {
                if (c == '_') {
                    c = ' ';
                }
            }

            inventory.push_back(Item(item_name, stringToItemType(type_str),
                effect,item_description,durability, max_durability));
        }
        file >> weapon_index;
        file >> armour_index;
        file.close();

        current_scene_id = scene_id;
        player.loadFromSave(name, health, lives, score,inventory, weapon_index, armour_index);

        cout << "Game successfully loaded! Welcome back, " << name << "!" << endl;
        success = true;
    }

    return success;
}