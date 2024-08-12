#include "Entity.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player : public Entity{
    private:
        int experience;
        int experience_to_next_level;
        int gold;
        int skill_points;
        int strength;
        int agility;
        int intelligence;
        int vitality;
        int dexterity;
        int luck;
    
    public:
        Player(std::string name);
};

inline Player::Player(std::string name) : Entity(name){
    this->experience = 0;
    this->experience_to_next_level = 100;
    this->gold = 0;
    this->skill_points = 0;
    this->strength = 5;
    this->agility = 5;
    this->intelligence = 5;
    this->vitality = 5;
    this->dexterity = 5;
    this->luck = 5;
}

#endif