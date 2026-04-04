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

// Runs the turn-based combat loop between player and enemy
void CombatScene::runCombat(Player& player) {
    cout << "\n-----Your enemy " << enemy.getName() << "'s stats-----"<< endl;
    cout << "| HP:  " << enemy.getHealth() << endl;
    cout << "| ATK: " << enemy.getAttack() << endl;
    cout << "| DEF: " << enemy.getDefense() << endl;

    Enemy currentEnemy = enemy;

    // pause for better effect of fight
    this_thread::sleep_for(chrono::milliseconds(1500));

    while (currentEnemy.isAlive() && player.isAlive()) {
        // Add random variance of -2 to +2 to attack damage
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

        // pause for better effect of fight
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Track lives before hit to detect if player died from this attack
        int lives_before = player.getLives();
        int enemyDamage = currentEnemy.getAttack() + (rand() % 5) - 2;
        if (enemyDamage < 0) {
            enemyDamage = 0;
        }

        player.takeDamage(enemyDamage);
        cout << currentEnemy.getName() << " attacks you for " << enemyDamage
             << " damage! (Your HP: " << player.getHealth() << ")" << endl;

        // If player lost a life from this hit, it exits combat, scene will retry
        if (player.getLives() < lives_before) {
            cout << "You have been defeated! Lives remaining: " << player.getLives() << endl;
            player.resetAfterDeath();
            break;
        }

        // pause for better effect of fight
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    if (currentEnemy.isAlive()) {
        cout << "\nYou were defeated by " << enemy.getName() << "..." << endl;
    }
    else {
        cout << "\nYou defeated " << enemy.getName() << "!" << endl;
        player.addScore(currentEnemy.getScoreReward());
        cout << "Your score increased by " << currentEnemy.getScoreReward() << endl;

        if (currentEnemy.getHasDrop()) {
            int drop_roll = rand() % 10;
            int threshold = 4; // 40% default for items

            // Keys have higher drop chance so player usually gets access to locked doors
            if (currentEnemy.getDropItem().getType() == ItemType::KEY) {
                threshold = 6; // 60% for keys
            }

            if (drop_roll < threshold) {
                cout << "After defeating the " << currentEnemy.getName() << " you receive loot "
                << currentEnemy.getDropItem().getName() << "!" << endl;
                player.addItem(currentEnemy.getDropItem());
            }
        }
    }
}

// Player chooses to fight or escape, combat runs, returns same scene if life was lost
int CombatScene::play(Player& player) {
    cout << "\n" << description << endl;
    int next = presentChoices(player);

    int lives_before = player.getLives();

    if (last_choice == 'A') {
        runCombat(player);
    } else {
        // 30% chance to escape, otherwise forced to fight
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

    // If a life was lost, return same scene so player will be fighting again
    if (player.getLives() < lives_before) {
        cout << "\nYou lost a life! Lives remaining: " << player.getLives() << endl;
        cout << "You recover and prepare to try again..." << endl;
        cout << "Open your inventory to re-equip before the next attempt." << endl;
        next = scene_id;
    }

    return next;
}