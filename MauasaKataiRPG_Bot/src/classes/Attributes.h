#include <array>

#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

class Attributes{
    private:
        int strength;
        int agility;
        int intelligence;
        int vitality;
        int dexterity;
        int luck;
    
    public:

        /**
         * @brief Default constructor of the Attributes class
         * @param attributes: array containing all the attributes to asign in order -> array<int, 6>
         * @attributes[0] -> strength
         * @attributes[1] -> agility
         * @attributes[2] -> intelligence
         * @attributes[3] -> vitality
         * @attributes[4] -> dexterity
         * @attributes[5] -> luck   
         * @return Attributes
        **/
        Attributes(std::array<int, 6> attributes): 
            strength(attributes[0]), 
            agility(attributes[1]), 
            intelligence(attributes[2]), 
            vitality(attributes[3]), 
            dexterity(attributes[4]), 
            luck(attributes[5]) {}

        /**
         * @brief Constructor of the Attributes class as a copy of another one
         * @param attributes: Attributes object to copy -> Attributes
         * @return Attributes
        **/
        Attributes(Attributes const &attributes) = default;

        /**
         * @brief Function that adds a set of attribute points to the player
         * @param attributes: all the 6 attributes even if its empty -> array<int, 6>
         * @attributes[0] -> strength
         * @attributes[1] -> agility
         * @attributes[2] -> intelligence
         * @attributes[3] -> vitality
         * @attributes[4] -> dexterity
         * @attributes[5] -> luck 
        **/
        void add_attribute_points(std::array<int, 6> attributes);

        /**
         * @brief Function that gets the attributes values
         * @return array<int, 6>
         * @attributes[0] -> strength
         * @attributes[1] -> agility
         * @attributes[2] -> intelligence
         * @attributes[3] -> vitality
         * @attributes[4] -> dexterity
         * @attributes[5] -> luck
        **/
        std::array<int, 6> get_attributes();
};

#endif