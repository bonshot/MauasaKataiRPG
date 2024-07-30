#include "Weapon.h"

#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity{
    private:
        std::string name;
        Weapon left_hand;
        Weapon right_hand;
        int level;
        int health;
        int mana;
        int conviction;
        int min_damage;
        int max_damage;
        int armor;
        int magic_resistance;
    
    public:
        Entity(std::string name);
}

Entity::Entity(std::string name){
    this->name = name;
    this->level = 1;
    this->health = 100;
    this->mana = 100;
    this->conviction = 100;
    this->min_damage = 0;
    this->max_damage = 0;
    this->armor = 5;
    this->magic_resistance = 5;
}

#endif