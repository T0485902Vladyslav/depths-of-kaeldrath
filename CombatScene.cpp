#include "CombatScene.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
using namespace std;

CombatScene::CombatScene(int cindex, string cdescription, string cchoiceA, string cchoiceB,
    string cconsequenceA, string cconsequenceB, int cnextSceneA, int cnextSceneB, Enemy cenemy)
: Scene(cindex, cdescription, cchoiceA, cchoiceB,
            cconsequenceA, cconsequenceB, cnextSceneA, cnextSceneB), enemy(cenemy){}

void CombatScene::runCombat(Player& player) {
    cout << "\n-----Your enemy " << enemy.getName() << "'s stats-----"<< endl;
    cout << "| HP:  " << enemy.getHealth() << endl;
    cout << "| ATK: " << enemy.getAttack() << endl;
    cout << "| DEF: " << enemy.getDefense() << endl;

    Enemy currentEnemy = enemy;

    this_thread::sleep_for(chrono::milliseconds(1500)); // pause for better effect of fight

    while (currentEnemy.isAlive() && player.isAlive()) {
        int playerDamage = player.getAttackDamage() + (rand() % 5) - 2;
        if (playerDamage < 0) {
            playerDamage = 0;
        }
        currentEnemy.takeDamage(playerDamage);
        player.reduceWeaponDurability();
        cout << "\nYou attack " << currentEnemy.getName() << " for " << playerDamage << " damage!"
             <<" (Enemy HP: " << currentEnemy.getHealth() << ")" << endl;

        if (!currentEnemy.isAlive()) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(1000)); // pause for better effect of fight

        int lives_before = player.getLives();
        int enemyDamage = currentEnemy.getAttack() + (rand() % 5) - 2;
        if (enemyDamage < 0) {
            enemyDamage = 0;
        }

        player.takeDamage(enemyDamage);
        cout << currentEnemy.getName() << " attacks you for " << enemyDamage
             << " damage! (Your HP: " << player.getHealth() << ")" << endl;

        if (player.getLives() < lives_before) {
            cout << "You have been defeated! Lives remaining: " << player.getLives() << endl;
            player.resetAfterDeath();
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(1000)); // pause for better effect of fight
    }

    if (currentEnemy.isAlive()) {
        cout << "\nYou were defeated by " << enemy.getName() << "..." << endl;
    }
    else {
        cout << "\nYou defeated " << enemy.getName() << "!" << endl;
        player.addScore(currentEnemy.getScoreReward());
        cout << "Your score increased by " << currentEnemy.getScoreReward() << endl;

        if (currentEnemy.getHasDrop()) {
            int dropRoll = rand() % 10;
            int threshold = 4; // 40% default for items

            if (currentEnemy.getDropItem().getType() == ItemType::KEY) {
                threshold = 6; // 60% for keys
            }

            if (dropRoll < threshold) {
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

    int lives_before = player.getLives();

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

    if (player.getLives() < lives_before) {
        cout << "\nYou lost a life! Lives remaining: " << player.getLives() << endl;
        cout << "You recover and prepare to try again..." << endl;
        cout << "Open your inventory to re-equip before the next attempt." << endl;
        next = scene_id;
    }

    return next;
}