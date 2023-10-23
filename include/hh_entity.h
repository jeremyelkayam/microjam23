#ifndef HH_ENTITY_H
#define HH_ENTITY_H

#include "bn_fixed_rect.h"
#include "bn_log.h"


namespace hh {
class entity {
public: 
    entity(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height, bn::fixed speed);
    void update();
    const bn::fixed_rect &hitbox() {return _hitbox;}
    const bn::fixed_point &pos() {return _pos;}
    void disable_movement() { _can_move = false;}

protected:
    //diagonal scalar -- approximately sqrt(2) / 2
    //multiply this by our speed to get the correct x and y components.
    // of speed, while traveling at a 45 degree angle.
    const bn::fixed _ds = bn::fixed(0.70710678118);

    /// @brief Represents directions in the increment of 45 degrees.
    // 0 is center right, and the . 
    // 8 is a special value indicating center.
    const int8_t _center = 8, _right = 0, _down_right = 1, 
        _down = 2, _down_left = 3, _left = 4, _up_left = 5,
        _up = 6, _up_right = 7;

    bn::fixed_point _pos;
    bn::fixed_rect _hitbox;
    bn::fixed _speed;

    uint8_t _direction;
    bool _can_move;
};

}

#endif