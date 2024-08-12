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
        Item();
        
        Item(std::string name, std::string type, std::string rarity, int price, std::string description);

        virtual ~Item();

        std::string get_name();
        std::string get_type();
        std::string get_rarity();
        int get_price();
        std::string get_description();  
};



/**
 *  @brief Default ructor for Item
 *  @return Item
**/
inline Item::Item()
    : name(""),
      type(""),
      rarity(""),
      price(0),
      description("")
    {}

/** 
 *  @brief ructor for Item
 *  @param name Name of the item -> string
 *  @param type Type of the item -> string
 *  @param rarity Rarity of the item -> string
 *  @param price Price of the item -> int
 *  @param description Description of the item -> string
 *  @return Item
**/
inline Item::Item(std::string name, std::string type, std::string rarity, int price, std::string description)
    : name(name),
      type(type),
      rarity(rarity),
      price(price),
      description(description)
    {}


/**
 * @brief Function that gets the name of the item
 * @return string
**/
inline std::string Item::get_name() {
    return this->name;
}

/**
 * @brief Function that gets the type of the item as is throwable, weapon, consumable, armor, etc.
 * @return string
**/
inline std::string Item::get_type() {
    return this->type;
}

/**
 * @brief Function that gets the rarity of the item as is common, uncommon, rare, epic, etc.
 * @return string
**/
inline std::string Item::get_rarity() {
    return this->rarity;
}

/**
 * @brief Function that gets the base price of the item
 * @return int
**/
inline int Item::get_price() {
    return this->price;
}

/**
 * @brief Function that gets the description of the item
 * @return string
**/
inline std::string Item::get_description() {
    return this->description;
}

#endif