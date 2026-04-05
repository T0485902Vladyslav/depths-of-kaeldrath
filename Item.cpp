#include "Item.h"
#include <iostream>
using namespace std;

// Standard constructor, max_durability is set equal to durability
Item::Item(string c_name, ItemType c_type, int c_effect_value, string c_description, int c_durability) {
    name = c_name;
    type = c_type;
    effect_value = c_effect_value;
    description = c_description;
    durability = c_durability;
    max_durability = c_durability;
}

// Load constructor,used when loading from save file to restore both durability values independently,
// because a loaded item may have been partially used before saving.
Item::Item(string c_name, ItemType c_type, int c_effect_value, string c_description, int c_durability, int c_max_durability) {
    name = c_name;
    type = c_type;
    effect_value = c_effect_value;
    description = c_description;
    durability = c_durability;
    max_durability = c_max_durability;
}

ItemType Item::getType() const {
    return type;
}
string Item::getName() const {
    return name;
}
int Item::getEffectValue() const {
    return effect_value;
}
string Item::getDescription() const {
    return description;
}
int Item::getDurability() const {
    return durability;
}
int Item::getMaxDurability() const {
    return max_durability;
}

// Returns true if item has run out of durability
bool Item::isBroken() const {
    bool broken = false;
    // FOOD and KEY types have no durability so they can't be broken
    if (type != ItemType::FOOD && type != ItemType::KEY && durability <= 0) {
        broken = true;
    }
    return broken;
}

// Decreases durability by 1 to use after each attack or hit taken
void Item::reduceDurability() {
    if (durability > 0) {
        durability--;
    }
}

// To print item name, description and effect value to user
void Item::printItemInfo() const {
    cout << "{" << name << "} " << description << endl;
    if (type != ItemType::KEY) {
        cout << "Effect: " << effect_value << endl;
    }
}