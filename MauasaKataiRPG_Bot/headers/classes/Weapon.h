#include "Item.h"
#include "Scales.h"
#include "Effects.h"
#include "Level.h"
#include <iostream>
#include <array>

#define MAX_LEVEL 100

#ifndef __WEPAON_H__
#define __WEAPON_H__

class Weapon : public Item{
    private:
        std::array<int, 2> damage;
        std::array<double, 2> critical;
        std::string damage_type;
        Scales scales;
        Effects effects;
        Level level;
        int player_level_required;

    public:
        Weapon();
        Weapon(std::array<int, 2> damage, std::array<double, 2> critical, std::string damage_type, Scales scales, Effects effects, Level level, int player_level_required);

        virtual ~Weapon();
        virtual void equip();
        virtual void unequip();
        void level_up();
        std::array<int, 2> get_damage();
        std::array<double, 2> get_critical();
};

inline void Weapon::level_up(){
    this->level.level_up();
}

inline std::array<int, 2> Weapon::get_damage(){
    return {this->damage[0], this->damage[1]};
}

inline std::array<double, 2> Weapon::get_critical(){
    return {this->critical[0], this->critical[1]};
}

#endif