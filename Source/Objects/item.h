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
    
    bool levelUp();

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

    int GetBlock() const { return block; }
    void SetBlock(int newBlock) { block = newBlock; }
    int GetSpecial() const { return special; }
    void SetSpecial(int newSpecial) { special = newSpecial; }


    virtual string getType() const override { return "OffHandItem"; }
};
#endif // ITEM_H