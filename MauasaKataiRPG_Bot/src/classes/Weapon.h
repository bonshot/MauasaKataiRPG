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

        /**
         * @brief Base constructor of the Weapon class, creates a weapon with default values
         * @return Weapon empty
        **/
        Weapon();

        /**
         * @brief Full constructor of the Weapon class, this constructor creates a weapon with all the values set
         * @param damage: array of two integers, the first is the minimum damage and the second is the maximum damage -> std::array<int, 2>
         * @param critical: array of two doubles, the first is the minimum critical chance and the second is the maximum critical chance -> std::array<double, 2>
         * @param damage_type: string with the type of damage the weapon does -> std::string
         * @param scales: Scales object with the scales of the weapon -> Scales
         * @param effects: Effects object with the effects of the weapon -> Effects
         * @param level: Level object with the level of the weapon -> Level
         * @param player_level_required: integer with the level required to use the weapon -> int
         * @return Weapon
        **/
        Weapon(std::array<int, 2> damage, std::array<double, 2> critical, std::string damage_type, Scales scales, Effects effects, Level level, int player_level_required):
            damage(damage),
            critical(critical),
            damage_type(damage_type),
            scales(scales),
            effects(effects),
            level(level),
            player_level_required(player_level_required)
        {}

        /**
         * @brief Destructor of the Weapon class, it will be declared on either one handed, or two handed
        **/
        virtual ~Weapon();

        /**
         * @brief Equip the weapon, it will be declared on either one handed, or two handed
        **/
        virtual void equip();

        /**
         * @brief Unequip the weapon, it will be declared on either one handed, or two handed
        **/
        virtual void unequip();

        /**
         * @brief Level up the weapon
        **/
        void level_up();

        /**
         * @brief Get the damage of the weapon
         * @return std::array<int, 2>
        **/
        std::array<int, 2> get_damage();

        /**
         * @brief Get the critical of the weapon
         * @return std::array<double, 2>
        **/
        std::array<double, 2> get_critical();
};


#endif