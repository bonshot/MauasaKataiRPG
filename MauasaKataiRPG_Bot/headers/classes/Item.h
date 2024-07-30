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
        
        Item(std::string name, std::string type, std::string rarity, int price, std::string description, int max_stack);

        virtual ~Item();

        std::string get_name() const;
        std::string get_type() const;
        std::string get_rarity() const;
        int get_price() const;
        std::string get_description() const;  
};



/**
 *  @brief Default constructor for Item
 *  @return Item
**/
Item::Item()
    : name(""),
      type(""),
      rarity(""),
      price(0),
      description(""),
      max_stack(0)
    {}

/** 
 *  @brief Constructor for Item
 *  @param name Name of the item -> string
 *  @param type Type of the item -> string
 *  @param rarity Rarity of the item -> string
 *  @param price Price of the item -> int
 *  @param description Description of the item -> string
 *  @param max_stack Maximum stack of the item -> int
 *  @return Item -> 
**/
Item::Item(std::string name, std::string type, std::string rarity, int price, std::string description, int max_stack)
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
std::string get_name() const{
    return this->name;
}

/**
 * @brief Function that gets the type of the item as is throwable, weapon, consumable, armor, etc.
 * @return string
**/
std::string get_type() const{
    return this->type;
}

/**
 * @brief Function that gets the rarity of the item as is common, uncommon, rare, epic, etc.
 * @return string
**/
std::string get_rarity() const{
    return this->rarity;
}

/**
 * @brief Function that gets the base price of the item
 * @return int
**/
int get_price() const{
    return this->price;
}

/**
 * @brief Function that gets the description of the item
 * @return string
**/
std::string get_description() const{
    return this->description;
}

#endif