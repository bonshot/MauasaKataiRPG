#include <iostream>
#include <cmath>

#ifndef __LEVEL_H__
#define __LEVEL_H__

class Level{
    private:
        int level;
        int experience;
        int experience_to_next_level;
        int max_level;
    
    public:

        /**
         * @brief Base constructor of the Level class, it handles the level and experience of either entities and items
         * @return Level
        **/
        Level():
            level(1),
            experience(0),
            experience_to_next_level(100), // set equation
            max_level(100)
        {}

        /**
         * @brief level up the entity or item if needed, it also updates the experience to next level
        **/
        void level_up();

        /**
         * @brief Add experience to the entity, it can be choose to be proportional (percentage of the level) or direct experience
         * @param exp: amount of experience or percentage of experience if proportional to add -> int
         * @param proportional: sets if the experience is proportional to the level or not -> bool
        **/
        void add_exp(int exp, bool proportional);
        
        /**
         * @brief Check if the entity or item is at max level
         * @return bool
        **/
        bool is_max_level();

        /**
         * @brief Get the level of the entity
         * @return int
        **/
        int get_level();

        /**
         * @brief Get the experience of the entity
         * @return int
        **/
        int get_experience();

        /**
         * @brief Get the experience needed to level up
         * @return int
        **/
        int get_experience_to_next_level();
};

#endif