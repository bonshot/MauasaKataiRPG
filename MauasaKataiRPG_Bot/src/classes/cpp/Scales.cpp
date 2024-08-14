#include "../Scales.h"

using namespace std;

array<double, SCALE_AMOUNT> Scales::get_scales(){
    return {
        this->scale_str, 
        this->scale_dex, 
        this->scale_int, 
        this->scale_fth, 
        this->scale_arm, 
        this->scale_hp, 
        this->scale_luck
    };
}