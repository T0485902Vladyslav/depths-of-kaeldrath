#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class ItemType {
    WEAPON,
    ARMOR,
    FOOD,
};

class Item {
private:
    ItemType type;
    string name;
    int effect_value;
    string description;
public:
    Item(string cname, ItemType ctype, int ceffect_value, string cdescription) {
        name = cname;
        type = ctype;
        effect_value = ceffect_value;
        description = cdescription;
    }
    ItemType getType() {
        return type;
    }
    string getName() {
        return name;
    }
    int getEffectValue() {
        return effect_value;
    }
    string getDescription() {
        return description;
    }
    void printItemInfo() const{
        cout << "{" << name << "}" << description << endl;
        cout << "Effect: " << effect_value << endl;
    }
};

class Player {
private:
    string name;
    int health;
    int lives;
    int attack_damage;
    int defense;
    int score;
    vector<Item> inventory;

    static const int MAX_HEALTH = 100;
    static const int MAX_INVENTORY = 10;
public:
    Player(string cname) {
        name = cname;
        health = MAX_HEALTH;
        lives = 3;
        attack_damage = 15;
        defense = 0;
        score = 0;
    }
    string getName() {
        return name;
    }
    int getHealth() {
        return health;
    }
    int getLives() {
        return lives;
    }
    int getAttackDamage() {
        return attack_damage;
    }
    int getDefense() {
        return defense;
    }
    int getScore() {
        return score;
    }

    void heal(int amount) {
        health += amount;
        if (health > MAX_HEALTH) {
            health = MAX_HEALTH;
        }
    }

    void showInventory() {
        if (inventory.empty()) {
            cout << "Your inventory is empty" << endl;
            return;
        }
        cout << "=== Inventory ===" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            inventory[i].printItemInfo();
        }
    }

    void showPlayerStats() const {
        cout << "===" << name << " 's Stats ===" << endl;
        cout << "Health: " << health << endl;
        cout << "Attack damage: " << attack_damage << endl;
        cout << "Defense: " << defense << endl;
        cout << "Lives: " << lives << endl;
        cout << "Score: " << score << endl;

    }
};

int main() {

}