#include "Weapon.h"
#include "Level.h"

#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity{
    private:
        std::string name;
        Weapon left_hand;
        Weapon right_hand;
        Level level;
        int health;
        int mana;
        int conviction;
        int min_damage;
        int max_damage;
        int armor;
        int magic_resistance;
    
    public:
    
        /**
         * @brief Construct a new Entity object, an entitie can be either a player or a monster, even a boss
         * @param name: name of the entity -> string
         * @return Entity
        **/
        Entity(std::string name);

};

inline Entity::Entity(std::string name){
    this->name = name;
    this->level = Level();
    this->health = 100;
    this->mana = 100;
    this->conviction = 100;
    this->min_damage = 0;
    this->max_damage = 0;
    this->armor = 5;
    this->magic_resistance = 5;
}

#endif