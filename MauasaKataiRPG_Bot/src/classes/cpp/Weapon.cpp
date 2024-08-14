#include "../Weapon.h"

using namespace std;

void Weapon::level_up(){
    this->level.level_up();
}

array<int, 2> Weapon::get_damage(){
    return {this->damage[0], this->damage[1]};
}

array<double, 2> Weapon::get_critical(){
    return {this->critical[0], this->critical[1]};
}