#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "GameMap.h"

using namespace std;

class Item {
    
    int id;
    string name;
    int value;
    int diffInt;
    int level;
    bool plus;
    float levelUp = 1.2f;

    public:

    Item() : id(-1), name("Placeholder"), value(-1), diffInt(0), level(0), plus(false) {}
    Item(int id, const string& name, int value, Difficulty diff, int level) : id(id), name(name), value(value), diffInt(static_cast<int>(diff)), level(level), plus(false) {}

    int GetID() const { return id; }
    string GetName() const { return name; }
    int GetValue() const { return value; }
    int GetLevel() const { return level; }
    
    void SetID(int newID) { id = newID; }
    void SetName(const string& newName) { name = newName; }
    void SetValue(int newValue) { value = newValue; }
    void SetDifficulty(Difficulty newDiff) { diffInt = static_cast<int>(newDiff); } 
    void SetLevel(int newLevel) { level = newLevel; }
    
    virtual bool levelUp();

    virtual string getType() const = 0;
};

class Weapon : public Item {
    
    int atk;
    
    public:

    Weapon() : Item(), atk(0) {}
    Weapon(int id, const string& name, int value, Difficulty diff, int level, int atk) : Item(id, name, value, diff, level), atk(atk) {}

    int GetAttack() const { return atk; }
    void SetAttack(int newAtk) { atk = newAtk; }

    virtual string getType() const override { return "Weapon"; }
};

class Armor : public Item {
    
    int def;
    
    public:

    Armor() : Item(), def(0) {}
    Armor(int id, const string& name, int value, Difficulty diff, int level, int def) : Item(id, name, value, diff, level), def(def) {}

    int GetDefense() const { return def; }
    void SetDefense(int newDef) { def = newDef; }

    virtual string getType() const override { return "Armor"; }
};

class OffHandItem : public Item {
    
    int block;
    int special;
    
    public:

    OffHandItem() : Item(), block(0) {}
    OffHandItem(int id, const string& name, int value, Difficulty diff, int level, int block) : Item(id, name, value, diff, level), block(block), special(0) {}
    OffHandItem(int id, const string& name, int value, Difficulty diff, int level, int block, int special) : Item(id, name, value, diff, level), block(block), special(special) {}
    OffHandItem(int id, const string& name, int value, Difficulty diff, int level, int special) : Item(id, name, value, diff, level), block(0), special(special) {}

    int GetBlock() const { return block; }
    void SetBlock(int newBlock) { block = newBlock; }
    int GetSpecial() const { return special; }
    void SetSpecial(int newSpecial) { special = newSpecial; }


    virtual string getType() const override { return "OffHandItem"; }
};

class Consumable : public Item {
    
    int held;
    int maxHeld;

    public:

    Consumable() : Item(), held(0), maxHeld(0) {}
    Consumable(int id, const string& name, int value, Difficulty diff, int level, int maxHeld) : Item(id, name, value, diff, level), held(1), maxHeld(maxHeld) {}
    Consumable(int id, const string& name, int value, Difficulty diff, int level, int held, int maxHeld) : Item(id, name, value, diff, level), held(held), maxHeld(maxHeld) {}

    int GetHeld() const { return held; }
    int GetMaxHeld() const { return maxHeld; }
    void SetHeld(int newHeld) { held = newHeld; }
    void SetMaxHeld(int newMaxHeld) { maxHeld = newMaxHeld; }

    virtual void pickUp();
    virtual void use();

    virtual string getType() const override { return "Consumable"; }
};

class HealingItem : public Consumable {
    
    int healAmount;

    public:

    HealingItem() : Consumable(), healAmount(0) {}
    HealingItem(int id, const string& name, int value, Difficulty diff, int level, int maxHeld, int healAmount) : Consumable(id, name, value, diff, level, maxHeld), healAmount(healAmount) {}
    HealingItem(int id, const string& name, int value, Difficulty diff, int level, int held, int maxHeld, int healAmount) : Consumable(id, name, value, diff, level, held, maxHeld), healAmount(healAmount) {}

    int GetHealAmount() const { return healAmount; }
    void SetHealAmount(int newHealAmount) { healAmount = newHealAmount; }

    virtual string getType() const override { return "Healing Item"; }
};

class Scroll : public Consumable {
    
    string spellName;

    public:

    Scroll() : Consumable(), spellName("NoSpell") {}
    Scroll(int id, const string& name, int value, Difficulty diff, int level, int maxHeld, const string& spellName) : Consumable(id, name, value, diff, level, maxHeld), spellName(spellName) {}
    Scroll(int id, const string& name, int value, Difficulty diff, int level, int held, int maxHeld, const string& spellName) : Consumable(id, name, value, diff, level, held, maxHeld), spellName(spellName) {}

    string GetSpellName() const { return spellName; }
    void SetSpellName(const string& newSpellName) { spellName = newSpellName; }

    virtual string getType() const override { return "Scroll"; }
};

class BuffItem : public Consumable {
    
    string buffType;
    int buffAmount;
    int duration;

    public:

    BuffItem() : Consumable(), buffType("NoBuff"), buffAmount(0), duration(0) {}
    BuffItem(int id, const string& name, int value, Difficulty diff, int level, int maxHeld, const string& buffType, int buffAmount, int duration) : Consumable(id, name, value, diff, level, maxHeld), buffType(buffType), buffAmount(buffAmount), duration(duration) {}
    BuffItem(int id, const string& name, int value, Difficulty diff, int level, int held, int maxHeld, const string& buffType, int buffAmount, int duration) : Consumable(id, name, value, diff, level, held, maxHeld), buffType(buffType), buffAmount(buffAmount), duration(duration) {}

    string GetBuffType() const { return buffType; }
    int GetBuffAmount() const { return buffAmount; }
    int GetDuration() const { return duration; }

    void SetBuffType(const string& newBuffType) { buffType = newBuffType; }
    void SetBuffAmount(int newBuffAmount) { buffAmount = newBuffAmount; }
    void SetDuration(int newDuration) { duration = newDuration; }

    virtual string getType() const override { return "Buff Item"; }
};

class LevelUpItem : public Consumable {
    
    public:

    LevelUpItem() : Consumable() {}
    LevelUpItem(int id, const string& name, int value, Difficulty diff, int level, int maxHeld) : Consumable(id, name, value, diff, level, maxHeld) {}
    LevelUpItem(int id, const string& name, int value, Difficulty diff, int level, int held, int maxHeld) : Consumable(id, name, value, diff, level, held, maxHeld) {}

    virtual string getType() const override { return "Level Up Item"; }
};

class PlayerLevelItem : public Consumable {


    
    public:

    PlayerLevelItem() : Consumable() {}
    PlayerLevelItem(int id, const string& name, int value, Difficulty diff, int level, int maxHeld) : Consumable(id, name, value, diff, level, maxHeld) {}
    PlayerLevelItem(int id, const string& name, int value, Difficulty diff, int level, int held, int maxHeld) : Consumable(id, name, value, diff, level, held, maxHeld) {}

    virtual string getType() const override { return "Player Level Item"; }
};
#endif // ITEM_H