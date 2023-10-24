#ifndef HH_GHOST_H
#define HH_GHOST_H

#include "hh_entity.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"


namespace hh {
class ghost : public entity {
public: 
    ghost(bn::fixed x, bn::fixed y, uint8_t initial_direction);
    void update();

private:
    bn::sprite_ptr _sprite;
    bn::sprite_animate_action<2> _anim;
};

}

#endif