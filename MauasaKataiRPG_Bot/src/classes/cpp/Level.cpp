#include "../Level.h"

using namespace std;

void Level::level_up(){
    if(this->level >= this->max_level){
        cout << "The player is already at max level" << endl;
        return;
    }
    this->level++;
    this->experience_to_next_level = pow(pow(2, this->get_level() / 20.0), 6) + 400;
}

void Level::add_exp(int exp, bool proportional){
    if(!this->is_max_level()){
        this->experience += (proportional)? (this->max_level / 100) * exp : exp;
        while(this->experience >= this->experience_to_next_level && !this->is_max_level()){
            this->level_up();
        }
    }
}

bool Level::is_max_level(){
    return this->level >= this->max_level;
}

int Level::get_level(){
    return this->level;
}

int Level::get_experience(){
    return this->experience;
}

int Level::get_experience_to_next_level(){
    return this->experience_to_next_level;
}