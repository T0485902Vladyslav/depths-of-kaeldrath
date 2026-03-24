#include "Enemy.h"

Enemy::Enemy(string c_name, int c_health, int c_attack, int c_defense, int c_score_reward)
    : drop_item("", ItemType::WEAPON, 0, "") {
    name = c_name;
    health = c_health;
    attack = c_attack;
    defense = c_defense;
    score_reward = c_score_reward;
    has_drop = false;
}

Enemy::Enemy(string c_name, int c_health, int c_attack, int c_defense, int c_score_reward, Item c_drop_item)
    : drop_item(c_drop_item) {
    name = c_name;
    health = c_health;
    attack = c_attack;
    defense = c_defense;
    score_reward = c_score_reward;
    has_drop = true;
}

string Enemy::getName() const {
    return name;
}
int Enemy::getHealth() const {
    return health;
}
int Enemy::getAttack() const {
    return attack;
}
int Enemy::getDefense() const {
    return defense;
}
int Enemy::getScoreReward() const {
    return score_reward;
}
bool Enemy::getHasDrop() const {
    return has_drop;
}
Item Enemy::getDropItem() const {
    return drop_item;
}
bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::takeDamage(int damage) {
    int actual_damage = damage - defense;
    if (actual_damage < 0) {
        actual_damage = 0;
    }
    health -= actual_damage;
    if (health < 0) {
        health = 0;
    }
}