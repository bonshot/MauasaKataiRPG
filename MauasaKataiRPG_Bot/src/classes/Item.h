#include <string>

#ifndef __ITEM_H__
#define __ITEM_H__

class Item{
    private:
        std::string name;
        std::string type;
        std::string rarity;
        int price;
        std::string description;
    public:
        /**
        *  @brief Default Constructor for Item
        *  @return Item
        **/
        Item():
            name(""),
            type(""),
            rarity(""),
            price(0),
            description("")
        {}
        
        /** 
        *  @brief Constructor for Item
        *  @param name Name of the item -> string
        *  @param type Type of the item -> string
        *  @param rarity Rarity of the item -> string
        *  @param price Price of the item -> int
        *  @param description Description of the item -> string
        *  @return Item
        **/
        Item(std::string name, std::string type, std::string rarity, int price, std::string description):
            name(name),
            type(type),
            rarity(rarity),
            price(price),
            description(description)
        {}

        /**
         * @brief Destroy the Item object
         * Abstract method
        **/
        virtual ~Item();

        /**
        * @brief Function that gets the name of the item
        * @return string
        **/
        std::string get_name();
        
        /**
        * @brief Function that gets the type of the item as is throwable, weapon, consumable, armor, etc.
        * @return string
        **/
        std::string get_type();

        /**
        * @brief Function that gets the rarity of the item as is common, uncommon, rare, epic, etc.
        * @return string
        **/
        std::string get_rarity();

        /**
        * @brief Function that gets the base price of the item
        * @return int
        **/
        int get_price();

        
        /**
        * @brief Function that gets the description of the item
        * @return string
        **/
        std::string get_description();  
};

#endif