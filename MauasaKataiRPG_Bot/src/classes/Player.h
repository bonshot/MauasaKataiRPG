#include "Entity.h"
#include "Attributes.h"
#include "Level.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player : public Entity{
    private:
        int gold;
        int skill_points;
        Level level;
        Attributes attributes;
    
    public:
    
        /**
         * @brief Base constructor of the Player class
         * @param name: name of the player -> std::string
         * @param attributes: attributes of the player -> Attributes
         * @return Player
        **/
        Player(std::string name, Attributes attributes) : 
            Entity(name), 
            attributes(attributes), 
            level(Level()), 
            gold(0), 
            skill_points(0) 
        {}
};


#endif