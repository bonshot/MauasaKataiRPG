#include <array>

#ifndef __EFFECTS_H__
#define __EFFECTS_H__

class Effects{
    private:
        double venom_chance;
        int venom_duration;
        
        double freeze_chance;
        int freeze_duration;

        double paralysis_chance;
        int paralysis_duration;

        int effect_damage_min;
        int effect_damage_max;
        double effect_chance;

    public:

        /**
         * @brief Default constructor for Effects class
        **/
        Effects();

        /**
         * @brief Constructor for Effects class
         * @param effects -> array<double, 9> containing the effects values
         * effects[0] -> venom_chance
         * effects[1] -> venom_duration
         * effects[2] -> freeze_chance
         * effects[3] -> freeze_duration
         * effects[4] -> paralysis_chance
         * effects[5] -> paralysis_duration
         * effects[6] -> effect_damage_min
         * effects[7] -> effect_damage_max
         * effects[8] -> effect_chance
         * @return Effects
        **/
        Effects(std::array<double, 9> effects): 
            venom_chance      (effects[0]), 
            venom_duration    (effects[1]), 
            freeze_chance     (effects[2]), 
            freeze_duration   (effects[3]), 
            paralysis_chance  (effects[4]), 
            paralysis_duration(effects[5]), 
            effect_damage_min (effects[6]), 
            effect_damage_max (effects[7]), 
            effect_chance     (effects[8])
        {}

        /**
         * @brief Function that gets the effects values
         * @return array<double, 9>
         * effects[0] -> venom_chance
         * effects[1] -> venom_duration
         * effects[2] -> freeze_chance
         * effects[3] -> freeze_duration
         * effects[4] -> paralysis_chance
         * effects[5] -> paralysis_duration
         * effects[6] -> effect_damage_min
         * effects[7] -> effect_damage_max
         * effects[8] -> effect_chance
        **/
        std::array<double, 9> get_effects();

        /**
         * @brief Set the effects object
         * 
         * @param effects -> array<double, 9> containing the effects values
         * effects[0] -> venom_chance
         * effects[1] -> venom_duration
         * effects[2] -> freeze_chance
         * effects[3] -> freeze_duration
         * effects[4] -> paralysis_chance
         * effects[5] -> paralysis_duration
         * effects[6] -> effect_damage_min
         * effects[7] -> effect_damage_max
         * effects[8] -> effect_chance
        **/
        void set_effects(std::array<double, 9> effects);
};

#endif