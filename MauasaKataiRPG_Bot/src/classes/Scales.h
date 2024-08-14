#include <array>

#define SCALE_AMOUNT 7

#ifndef __SCALES_H__
#define __SCALES_H__

class Scales{
    protected:
        double scale_str;
        double scale_dex;
        double scale_int;
        double scale_fth;
        double scale_arm;
        double scale_hp;
        double scale_luck;

    public:

        /**
         * @brief Construct a new Scales::Scales object with all values set to the requested
         * @param scale_str  The strength factor     -> array[0]
         * @param scale_dex  The dexterity factor    -> array[1]
         * @param scale_int  The intelligence factor -> array[2]
         * @param scale_fth  The faith factor        -> array[3]
         * @param scale_arm  The armor factor        -> array[4]
         * @param scale_hp   The health factor       -> array[5]
         * @param scale_luck The luck factor         -> array[6]
         * @return Scales
        **/
        Scales(std::array<double, SCALE_AMOUNT> scales):
            scale_str(scales[0]),
            scale_dex(scales[1]),
            scale_int(scales[2]),
            scale_fth(scales[3]),
            scale_arm(scales[4]),
            scale_hp(scales[5]),
            scale_luck(scales[6])
        {}
        
        /**
         *  @brief Get an array of all the scales
         *  @return Array of doubles:
         *  @ [0] -> scale_str
         *  @ [1] -> scale_dex
         *  @ [2] -> scale_int
         *  @ [3] -> scale_fth
         *  @ [4] -> scale_arm
         *  @ [5] -> scale_hp
         *  @ [6] -> scale_luck
        **/
        std::array<double, SCALE_AMOUNT> get_scales();
};

#endif