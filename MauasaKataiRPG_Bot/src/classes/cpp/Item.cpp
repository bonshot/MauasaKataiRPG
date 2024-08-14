#include "../Item.h"

using namespace std;

string Item::get_name() {
    return this->name;
}

string Item::get_type() {
    return this->type;
}

string Item::get_rarity() {
    return this->rarity;
}

int Item::get_price() {
    return this->price;
}

string Item::get_description() {
    return this->description;
}