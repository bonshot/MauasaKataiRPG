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
        Effects();
        Effects(std::array<double, 9> effects);

        std::array<double, 9> get_effects();
        void set_effects(std::array<double, 9> effects);
};

inline Effects::Effects(std::array<double, 9> effects) : 
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

inline std::array<double, 9> Effects::get_effects(){
    return {
                this->venom_chance, 
        (double)this->venom_duration, 
                this->freeze_chance, 
        (double)this->freeze_duration, 
                this->paralysis_chance, 
        (double)this->paralysis_duration, 
        (double)this->effect_damage_min, 
        (double)this->effect_damage_max, 
                this->effect_chance
    };
}

inline void Effects::set_effects(std::array<double, 9> effects){
    this->venom_chance       = effects[0];
    this->venom_duration     = effects[1];
    this->freeze_chance      = effects[2];
    this->freeze_duration    = effects[3];
    this->paralysis_chance   = effects[4];
    this->paralysis_duration = effects[5];
    this->effect_damage_min  = effects[6];
    this->effect_damage_max  = effects[7];
    this->effect_chance      = effects[8];
}

#endif