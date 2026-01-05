#include <cmath>

#include "player.h"

using namespace std;

bool Player::LevelUpAttacker() {
    
    if (attackerLevel >= maxLevel) {
        return false;
    }

    attackerLevel++;
    int hpIncrease = baseHP - static_cast<int>(floor(40 * log(attackerLevel))); 
    if(hpIncrease < 7) {
        hpIncrease = 7; 
    }
    maxHP += hpIncrease;
    attack += attackerLevel; 
    defense += 2; 
    critRate += 2; 
    critDamage += 4; 
    skillPoints = static_cast<int>(skillPoints * 1.1);

    if(attackerLevel <= 15) {
        attackCoefficient *= 1.05;
    }
    else {
        attackCoefficient *= 1.02;
    }

    return true;

}

bool Player::LevelUpTank() {
    
    if (tankLevel >= maxLevel) {
        return false;
    }

    tankLevel++;
    int hpIncrease = baseHP - static_cast<int>(floor(20 * log(tankLevel))); 
    if(hpIncrease < 15) {
        hpIncrease = 15; 
    }
    maxHP += hpIncrease;
    tankAttack += tankLevel; 
    defense += 2 + static_cast<int>(ceil(tankLevel / 2.0)); 
    critRate += 1; 
    critDamage += 2; 
    skillPoints = static_cast<int>(skillPoints * 1.1);

    return true;

}

bool Player::LevelUpMage() {
    
    if (mageLevel >= maxLevel) {
        return false;
    }

    mageLevel++;
    int hpIncrease = baseHP - static_cast<int>(floor(40 * log(mageLevel))); 
    if(hpIncrease < 7) {
        hpIncrease = 7; 
    }
    maxHP += hpIncrease;
    magicAttack += mageLevel * 2; 
    defense += 1; 
    critRate += 2; 
    critDamage += 3; 
    skillPoints = static_cast<int>(skillPoints * 1.13);

    return true;

}