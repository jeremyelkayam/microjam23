#ifndef HH_BAT_H
#define HH_BAT_H

#include "hh_entity.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"


namespace hh {
class bat : public entity {
public: 
    bat(bn::fixed x, bn::fixed y, uint8_t initial_direction, bn::fixed tempo);
    void update();

private:
    bn::sprite_ptr _sprite;
    bn::sprite_vertical_flip_toggle_action _anim;
    const uint8_t _turn_time;
    uint8_t _timer;
};

}

#endif