#pragma once
#include <string>
#include "Item.h"
using namespace std;

class Enemy {
private:
    string name;
    int health;
    int attack;
    int defense;
    int score_reward;
    bool has_drop;
    Item drop_item;
public:
    // Constructor without drop
    Enemy(string c_name, int c_health, int c_attack, int c_defense, int c_score_reward);
    // Constructor with drop
    Enemy(string c_name, int c_health, int c_attack, int c_defense, int c_score_reward, Item c_drop_item);

    string getName() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;
    int getScoreReward() const;
    bool getHasDrop() const;
    Item getDropItem() const;
    bool isAlive() const;

    void takeDamage(int damage);
};