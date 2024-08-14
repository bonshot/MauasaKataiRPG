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
        Entity(std::string name): name(name), level(Level()), health(100), mana(100), conviction(100), min_damage(0), max_damage(0), armor(5), magic_resistance(5) {}

};

#endif