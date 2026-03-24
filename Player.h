#pragma once
#include <string>
#include <vector>
#include "Item.h"
using namespace std;
 
class Player {
private:
    string name;
    int health;
    int lives;
    int base_attack;
    int defense;
    int score;
    vector<Item> inventory;
    int equipped_weapon_index;
    int equipped_armour_index;

    void printInventoryList() const;
    void printEquipped() const;
    int getItemNumber();
 
public:
    Player(const string &cname);
    Player();
 
    string getName();
    int getHealth();
    int getLives();
    int getAttackDamage() const;
    int getDefense()      const;
    int getScore();
 
    void heal(int amount);
    void takeDamage(int amount);
    void reduceWeaponDurability();
    bool isAlive() const;
    void addScore(int amount);
    bool addItem(const Item& item);
    void equipItem(int index);
    void useFood(int index);
    void showInventory();
    void showPlayerStats() const;
};