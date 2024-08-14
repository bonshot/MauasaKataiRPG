#include "../Attributes.h"

void Attributes::add_attribute_points(std::array<int, 6> attributes){
    this->strength     += attributes[0];
    this->agility      += attributes[1];
    this->intelligence += attributes[2];
    this->vitality     += attributes[3];
    this->dexterity    += attributes[4];
    this->luck         += attributes[5];
}

std::array<int, 6> Attributes::get_attributes(){
    return {
        this->strength, 
        this->agility, 
        this->intelligence, 
        this->vitality, 
        this->dexterity, 
        this->luck
    };
}