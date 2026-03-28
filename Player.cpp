#include "Player.h"
#include <iostream>
#include <limits>
using namespace std;

Player::Player(const string &cname) {
    name = cname;
    health = MAX_HEALTH;
    lives = 3;
    base_attack = 10;
    defense = 0;
    score = 0;
    equipped_weapon_index = -1;
    equipped_armour_index = -1;
}

Player::Player() {
    name = "";
    health = MAX_HEALTH;
    lives = 3;
    base_attack = 10;
    defense = 0;
    score = 0;
    equipped_weapon_index = -1;
    equipped_armour_index = -1;
}

string Player::getName() {
    return name;
}
int Player::getHealth() {
    return health;
}
int Player::getLives() {
    return lives;
}
int Player::getScore() {
    return score;
}

int Player::getAttackDamage() const {
    int attack = base_attack;
    if (equipped_weapon_index != -1 && !inventory[equipped_weapon_index].isBroken()) {
        attack = base_attack + inventory[equipped_weapon_index].getEffectValue();
    }
    return attack;
}

int Player::getDefense() const {
    int defense = 0;

    if (equipped_armour_index != -1 && !inventory[equipped_armour_index].isBroken()) {
        defense = inventory[equipped_armour_index].getEffectValue();
    }

    return defense;
}

vector<Item> Player::getInventory() const {
    return inventory;
}

int Player::getEquippedWeaponIndex() const {
    return equipped_weapon_index;
}

int Player::getEquippedArmourIndex() const {
    return equipped_armour_index;
}

void Player::loadFromSave(string s_name, int s_health, int s_lives, int s_score,
    vector<Item> s_inventory, int s_weapon_index, int s_armour_index) {

    name = s_name;
    health = s_health;
    lives = s_lives;
    score = s_score;
    inventory = s_inventory;
    equipped_weapon_index = s_weapon_index;
    equipped_armour_index = s_armour_index;
}

void Player::heal(int amount) {
    health += amount;
    if (health > MAX_HEALTH) {
        health = MAX_HEALTH;
    }
}

void Player::takeDamage(int amount) {
    int actualDamage = amount - getDefense();
    if (actualDamage < 0) actualDamage = 0;
    health -= actualDamage;

    if (equipped_armour_index != -1) {
        inventory[equipped_armour_index].reduceDurability();
        if (inventory[equipped_armour_index].isBroken()) {
            cout << "Your " << inventory[equipped_armour_index].getName() << " broke" << endl;
            equipped_armour_index = -1;
        }
    }

    if (health <= 0) {
        health = 0;
        lives--;
        if (lives > 0) {
            health = MAX_HEALTH;
            cout << "You lost a life! Lives remaining: " << lives << endl;
        }
    }
}

void Player::reduceWeaponDurability() {
    if (equipped_weapon_index != -1) {
        inventory[equipped_weapon_index].reduceDurability();

        if (inventory[equipped_weapon_index].isBroken()) {
            cout << "Your " << inventory[equipped_weapon_index].getName() << " broke" << endl;
            equipped_weapon_index = -1;
        }
    }
}

bool Player::isAlive() const {
    return lives > 0;
}

void Player::addScore(int amount) {
    score += amount;
}

bool Player::addItem(const Item& item) {
    bool success = false;

    if (inventory.size() < MAX_INVENTORY) {
        inventory.push_back(item);
        cout << "You picked up: " << item.getName() << endl;
        cout << "To equip, use or swap the item, open your inventory" << endl;
        success = true;
    }
    else {
        cout << "Inventory is full." << endl;
    }

    return success;
}

void Player::equipItem(int index) {
    if (index < 0 || index >= (int)inventory.size()) {
        cout << "\nInvalid item index." << endl;
    }
    else {

        Item& item = inventory[index];
        ItemType type = item.getType();

        if (type == ItemType::WEAPON) {
            equipped_weapon_index = index;
            cout << "\nEquipped weapon: " << item.getName() << endl;
        }
        else if (type == ItemType::ARMOUR) {
            equipped_armour_index = index;
            cout << "\nEquipped armour: " << item.getName() << endl;
        }
        else {
            cout << "\nThis item cannot be equipped." << endl;
        }
    }
}

void Player::useFood(int index) {
    if (index < 0 || index >= (int)inventory.size()) {
        cout << "Invalid item." << endl;
    }
    else if (inventory[index].getType() != ItemType::FOOD) {
        cout << "You can only use food items." << endl;
    }
    else {
        Item& item = inventory[index];
        heal(item.getEffectValue());

        cout << "You used " << item.getName() << ". Health +" << item.getEffectValue() << endl;
        cout << "Current health: " << health << "/" << MAX_HEALTH << endl;

        inventory.erase(inventory.begin() + index);

        if (equipped_weapon_index > index) {
            equipped_weapon_index--;
        } else if (equipped_weapon_index == index) {
            equipped_weapon_index = -1;
        }

        if (equipped_armour_index > index) {
            equipped_armour_index--;
        } else if (equipped_armour_index == index) {
            equipped_armour_index = -1;
        }
    }
}

void Player::printInventoryList() const {
    cout << "\n=== Inventory ===" << endl;

    if (inventory.empty()) {
        cout << "Your inventory is empty\n";
    }
    else {
        for (int i = 0; i < (int)inventory.size(); i++) {
            cout << i + 1 << ") ";
            inventory[i].printItemInfo();

            if (inventory[i].getType() == ItemType::WEAPON || inventory[i].getType() == ItemType::ARMOUR) {
                cout << "Durability: " << inventory[i].getDurability() << "/" << inventory[i].getMaxDurability() << "\n";
            }
        }
    }
}

void Player::printEquipped() const {
    cout << "\n=== Equipped ===" << endl;

    if (equipped_weapon_index != -1) {
        const Item& w = inventory[equipped_weapon_index];
        cout << "Weapon: " << w.getName() << " (Durability: " << w.getDurability() << "/" << w.getMaxDurability() << ")" << endl;
    }
    else {
        cout << "Weapon: none (base attack: " << base_attack << ")" << endl;
    }

    if (equipped_armour_index != -1) {
        const Item& a = inventory[equipped_armour_index];
        cout << "Armour: " << a.getName() << " (Durability: " << a.getDurability() << "/" << a.getMaxDurability() << ")" << endl;
    }
    else {
        cout << "Armour: none" << endl;
    }
}

int Player::getItemNumber() {
    int num = 0;
    bool valid = false;

    while (!valid) {
        cout << "Enter item number: ";

        string numLine;
        getline(cin, numLine);

        if (numLine.empty()) {
            cout << "Input cannot be blank." << endl;

        }else {
            try {
                size_t pos;
                num = stoi(numLine, &pos);

                if (pos != numLine.size()) {
                    cout << "Invalid input. Enter a number." << endl;
                }
                else if (num <= 0) {
                    cout << "Number must be greater than 0." << endl;
                }
                else {
                    valid = true;
                }
            }
            catch (...) {
                cout << "Invalid input. Enter a number." << endl;
            }
        }
    }
    return num - 1;
}

void Player::showInventory() {
    bool running = true;

    while (running) {

        printInventoryList();
        printEquipped();

        cout << "\nE) Equip item   U) Use food   B) Back" << endl;
        cout << "Choice: ";

        string line;
        getline(cin, line);

        if (line.empty()) {
            cout << "Input cannot be blank." << endl;
        }
        else {
            char opt = toupper(line[0]);

            if (opt == 'B') {
                running = false;
            }
            else if (opt == 'E') {
                equipItem(getItemNumber());
            }
            else if (opt == 'U') {
                useFood(getItemNumber());
            }
            else {
                cout << "Invalid choice. Enter E, U or B." << endl;
            }
        }
    }
}

void Player::showPlayerStats() const {
    cout << "===" << name << "'s Stats ===" << endl;
    cout << "Health: " << health << "/" << MAX_HEALTH << endl;
    cout << "Damage: " << getAttackDamage() << endl;
    cout << "Defense: " << getDefense() << endl;
    cout << "Lives: " << lives << endl;
    cout << "Score: " << score << endl;
}