#pragma once
#include <string>
using namespace std;

enum class ItemType {
    WEAPON,
    ARMOUR,
    FOOD,
};

static const int MAX_HEALTH = 100;
static const int MAX_INVENTORY = 10;

class Item {
private:
    ItemType type;
    string name;
    int effect_value;
    string description;
    int durability;
    int max_durability;
public:
    Item(string c_name, ItemType c_type, int c_effect_value, string c_description, int c_durability = 0);

    ItemType getType() const;
    string getName() const;
    int getEffectValue() const;
    string getDescription() const;
    int getDurability()  const;
    int getMaxDurability() const;
    bool isBroken() const;
    void reduceDurability();
    void printItemInfo() const;
};