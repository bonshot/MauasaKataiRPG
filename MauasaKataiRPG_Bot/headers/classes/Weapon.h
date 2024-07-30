#include "Item.h"
#include "Scales.h"

#ifndef __WEPAON_H__
#define __WEAPON_H__

class Weapon : public Item{
    private:
        int min_damage;
        int max_damage;
        int player_level_required;
        Scales scales;
        double critical_chance;
        double critical_damage;
        std::string damage_type;
        double venom_chance;        // Effects class
        int venom_duration;
        double freeze_chance;
        int freeze_duration;
        double paralysis_chance;
        int paralysis_duration;
        int effect_damage_min;
        int effect_damage_max;
        double effect_chance;
        int level;      // Leveling class with items needed
        int max_level;

    public:
        Weapon();
        Weapon(std::string name, std::string type, std::string rarity, int price, std::string description, int max_stack, int min_damage, int max_damage, int attack_speed, int critical_chance, int critical_damage, int durability);

        virtual ~Weapon();
        virtual void equip();
        virtual void unequip();

        void level_up();

        int get_min_damage() const;
        int get_max_damage() const;
        int get_attack_speed() const;
        int get_critical_chance() const;
        int get_critical_damage() const;
        int get_durability() const;
};

#endif