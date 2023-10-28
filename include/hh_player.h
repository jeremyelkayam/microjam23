#ifndef HH_PLAYER_H
#define HH_PLAYER_H

#include "bn_sprite_ptr.h"
#include "hh_entity.h"
#include "bn_random.h"
#include "bn_sound_items.h"


namespace hh
{
class player : public entity {
public: 
    player(bn::fixed x, bn::fixed y, bn::fixed tempo);
    virtual void update();
    virtual void lights_on(bn::random &rand);
    void take_button_input();
    void rotate_eyes();

private:
    bn::sprite_ptr _eyes, _body;
    const uint8_t _footsteps_interval;
    uint8_t _footsteps_timer;
};

}

#endif
