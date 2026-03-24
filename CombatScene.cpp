#include "CombatScene.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
using namespace std;

CombatScene::CombatScene(int c_index, string c_description, string c_choice_A, string c_choice_B,
    string c_consequence_A, string c_consequence_B, int c_next_scene_A, int c_next_scene_B, Enemy c_enemy)
: Scene(c_index, c_description, c_choice_A, c_choice_B,
            c_consequence_A, c_consequence_B, c_next_scene_A, c_next_scene_B), enemy(c_enemy){}

void CombatScene::runCombat(Player& player) {
    cout << "\n-----Your enemy " << enemy.getName() << "'s stats-----"<< endl;
    cout << "| HP:  " << enemy.getHealth() << endl;
    cout << "| ATK: " << enemy.getAttack() << endl;
    cout << "| DEF: " << enemy.getDefense() << endl;

    Enemy currentEnemy = enemy;

    this_thread::sleep_for(chrono::milliseconds(1500));

    while (currentEnemy.isAlive() && player.isAlive()) {
        int playerDamage = player.getAttackDamage() + (rand() % 5) - 2;
        if (playerDamage < 0) {
            playerDamage = 0;
        }
        currentEnemy.takeDamage(playerDamage);
        player.reduceWeaponDurability();
        cout << "\nYou attack " << currentEnemy.getName() << " for " << playerDamage << " damage!" <<
            " (Enemy HP: " << currentEnemy.getHealth() << ")" << endl;

        if (!currentEnemy.isAlive()) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(1000)); // pause for better effect of fight

        int enemyDamage = currentEnemy.getAttack() + (rand() % 5) - 2;
        if (enemyDamage < 0) {
            enemyDamage = 0;
        }
        player.takeDamage(enemyDamage);
        cout << currentEnemy.getName() << " attacks you for " << enemyDamage << " damage!" <<
            " (Your HP: " << player.getHealth() << ")" << endl;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    if (currentEnemy.isAlive()) {
        cout << "\nYou were defeated by " << enemy.getName() << "..." << endl;
    }else {
        cout << "\nYou defeated " << enemy.getName() << "!" << endl;
        player.addScore(currentEnemy.getScoreReward());
        cout << "Your score increased by " << currentEnemy.getScoreReward() << endl;

        if (currentEnemy.getHasDrop()) {
            int dropRoll = rand() % 10;
            if (dropRoll < 4) {
                cout << "After defeating the " << currentEnemy.getName() << " you receive loot "
                << currentEnemy.getDropItem().getName() << "!" << endl;
                player.addItem(currentEnemy.getDropItem());
            }
        }
    }
}

int CombatScene::play(Player& player) {
    cout << "\n" << description << endl;
    int next = presentChoices(player);

    if (last_choice == 'A') {
        runCombat(player);
    } else {
        int roll = rand() % 10;
        if (roll < 3) {
            cout << "\nYou managed to escape, but not without a hit..." << endl;
            player.takeDamage(15);
            cout << "You take 15 damage while running" << endl;
        } else {
            cout << "\nYou failed to avoid fight! The enemy attacks!" << endl;
            int enemyDamage = enemy.getAttack() + (rand() % 5) - 2;
            player.takeDamage(enemyDamage);
            cout << enemy.getName() << " hits you for " << enemyDamage << " damage." << endl;
            cout << "You are forced to fight!" << endl;
            runCombat(player);
        }
    }

    return next;
}