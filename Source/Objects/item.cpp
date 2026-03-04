#include <iostream>

#include "item.h"

using namespace std;

bool Weapon::levelUp() {
    if (!Item::levelUp()) return false;
    atk = static_cast<int>(atk * levelUpMult);
    return true;
}

bool Armor::levelUp() {
    if (!Item::levelUp()) return false;
    def = static_cast<int>(def * levelUpMult);
    return true;
}

bool OffHandItem::levelUp() {
    if (!Item::levelUp()) return false;
    block = static_cast<int>(block * levelUpMult);
    return true;
}

bool HealingItem::levelUp() {
    if (!Consumable::levelUp()) return false;
    healAmount = static_cast<int>(healAmount * levelUpMult);
    return true;
}

bool BuffItem::levelUp() {
    if (!Consumable::levelUp()) return false;
    buffAmount = static_cast<int>(buffAmount * levelUpMult);
    duration = static_cast<int>(duration * levelUpMult);
    return true;
}