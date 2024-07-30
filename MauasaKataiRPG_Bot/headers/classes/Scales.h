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
         * @brief Construct a new Scales::Scales object with all values set to 0
         * @return Scales
        **/
        Scales();

        /**
         * @brief Construct a new Scales::Scales object with all values set to the requested
         * @param scale_str  The strength factor     -> double
         * @param scale_dex  The dexterity factor    -> double
         * @param scale_int  The intelligence factor -> double
         * @param scale_fth  The faith factor        -> double
         * @param scale_arm  The armor factor        -> double
         * @param scale_hp   The health factor       -> double
         * @param scale_luck The luck factor         -> double
         * @return Scales
        **/
        Scales(double scale_str, double scale_dex, double scale_int, double scale_fth, double scale_arm, double scale_hp, double scale_luck);
        
        /**
         *  @brief Get the Scales object
         *  @return Scales
        **/
        Scales get_scales();

        /**
         *  @brief Get the strength scale factor
         *  @return double
        **/
        double get_scale_str() const;

        /**
         *  @brief Get the dexterity scale factor
         *  @return double
        **/
        double get_scale_dex() const;

        /**
         *  @brief Get the intelligence scale factor
         *  @return double
        **/
        double get_scale_int() const;

        /**
         *  @brief Get the faith scale factor
         *  @return double
        **/
        double get_scale_fth() const;

        /**
         *  @brief Get the armor scale factor
         *  @return double
        **/
        double get_scale_arm() const;

        /**
         *  @brief Get the health points scale factor
         *  @return double
        **/
        double get_scale_hp() const;

        /**
         *  @brief Get the luck scale factor
         *  @return double
        **/
        double get_scale_luck() const;
};

Scales::Scales()
    : scale_str(0),
      scale_dex(0),
      scale_int(0),
      scale_fth(0),
      scale_arm(0),
      scale_hp(0),
      scale_luck(0)
    {}

Scales::Scales(double scale_str, double scale_dex, double scale_int, double scale_fth, double scale_arm, double scale_hp, double scale_luck)
    : scale_str(scale_str),
      scale_dex(scale_dex),
      scale_int(scale_int),
      scale_fth(scale_fth),
      scale_arm(scale_arm),
      scale_hp(scale_hp),
      scale_luck(scale_luck)
    {}

Scales::get_scales(){
    return *this;
}

double Scales::get_scale_str() const{
    return this->scale_str;
}

double Scales::get_scale_dex() const{
    return this->scale_dex;
}

double Scales::get_scale_int() const{
    return this->scale_int;
}

double Scales::get_scale_fth() const{
    return this->scale_fth;
}

double Scales::get_scale_arm() const{
    return this->scale_arm;
}

double Scales::get_scale_hp() const{
    return this->scale_hp;
}

double Scales::get_scale_luck() const{
    return this->scale_luck;
}

#endif