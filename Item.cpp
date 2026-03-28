#include "Item.h"
#include <iostream>
using namespace std;

Item::Item(string c_name, ItemType c_type, int c_effect_value, string c_description, int c_durability) {
    name = c_name;
    type = c_type;
    effect_value = c_effect_value;
    description = c_description;
    durability = c_durability;
    max_durability = c_durability;
}

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

bool Item::isBroken() const {
    bool broken = false;
    if (type != ItemType::FOOD && durability <= 0) {
        broken = true;
    }
    return broken;
}

void Item::reduceDurability() {
    if (durability > 0) {
        durability--;
    }
}

void Item::printItemInfo() const {
    cout << "{" << name << "} " << description << endl;
    cout << "Effect: " << effect_value << endl;
}