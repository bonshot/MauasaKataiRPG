#include "../Effects.h"

std::array<double, 9> Effects::get_effects(){
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

void Effects::set_effects(std::array<double, 9> effects){
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