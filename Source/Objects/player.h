#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

/* Players can have 4 different level up types and damage types.

    Level Up Types:
    
    1. Attacker - Is focused on damage gains more than anything else. Will have lower HP and Defense gains, but higher damage increases. Level up skills will focus on physical damage. Very item dependent.
    2. Tank - Is focused on survivability. Gains more HP and Defense, but lower damage increases. Level ups will not usually have skills, but will have higher stat increases. Will be item dependent, but not as much as attacker.
    3. Mage - Is focused on magic damage and utility. Gains moderate HP and Defense, but high magic damage increases and much strongre skills. Likely won't care much about items, as they largely will not affect the damage of skills, but scrolls to learn more abilities will be valuable.
    4. Balanced - A mix of all three. Moderate increases to HP, Defense, and all types of damage. Skills will be a mix of physical and magical damage, though not as strong as a pure mage. Will care about items, but not as much as an attacker or tank. Based on my experience in other similar games, I strongly doubt this will be a preferred playstyle for most players. The main value I can see is that these level ups won't feel wasted on other classes. 

*/


class Player {
    
    int maxHP;
    int currentHP;
    int baseHP;
    int attack;
    int attackCoefficient;
    int tankAttack;
    int defense;
    int magicAttack;
    int critRate;
    int critDamage;
    int attackerLevel;
    int tankLevel;
    int mageLevel;
    int balancedLevel;
    int maxLevel = 20;

    public:

    Player() : maxHP(100), currentHP(100), baseHP(100), attack(10), attackCoefficient(2), tankAttack(10), defense(5), magicAttack(10), critRate(5), critDamage(20), attackerLevel(1), tankLevel(1), mageLevel(1), balancedLevel(1) {}

    int GetMaxHP() const { return maxHP; }
    int GetCurrentHP() const { return currentHP; }
    int GetAttack() const { return attack; }
    int GetAttackCoefficient() const { return attackCoefficient; }
    int GetTankAttack() const { return tankAttack; }
    int GetDefense() const { return defense; }
    int GetMagicAttack() const { return magicAttack; }
    int GetCriticalChance() const { return critRate; }
    int GetCriticalDamage() const { return critDamage; }
    int GetAttackerLevel() const { return attackerLevel; }
    int GetTankLevel() const { return tankLevel; }
    int GetMageLevel() const { return mageLevel; }
    int GetBalancedLevel() const { return balancedLevel; }

    void SetMaxHP(int newMaxHP) { maxHP = newMaxHP; }
    void SetCurrentHP(int newCurrentHP) { currentHP = newCurrentHP; }
    void SetAttack(int newAttack) { attack = newAttack; }
    void SetAttackCoefficient(int newAttackCoefficient) { attackCoefficient = newAttackCoefficient; }
    void SetTankAttack(int newTankAttack) { tankAttack = newTankAttack; }
    void SetDefense(int newDefense) { defense = newDefense; }
    void SetMagicAttack(int newMagicAttack) { magicAttack = newMagicAttack; }
    void SetCriticalChance(int newCritRate) { critRate = newCritRate; }
    void SetCriticalDamage(int newCritDamage) { critDamage = newCritDamage; }
    void SetAttackerLevel(int newAttackerLevel) { attackerLevel = newAttackerLevel; }
    void SetTankLevel(int newTankLevel) { tankLevel = newTankLevel; }
    void SetMageLevel(int newMageLevel) { mageLevel = newMageLevel; }
    void SetBalancedLevel(int newBalancedLevel) { balancedLevel = newBalancedLevel; }

    bool LevelUpAttacker();
    bool LevelUpTank();
    bool LevelUpMage();
    bool LevelUpBalanced();

    void DealDamage(int damage, int enemyDefense);
    void TakeDamage(int damage); // may also need monster class.
    bool isCrit() const;

};

#endif // PLAYER_H