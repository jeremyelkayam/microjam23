#ifndef HH_MONSTER_H
#define HH_MONSTER_H

#include "bn_fixed_rect.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"


namespace hh {
class monster {
public: 
    monster(bn::fixed x, bn::fixed y);
    void update();

private:
    bn::fixed_point _pos;
    bn::fixed_rect _hitbox;
    bn::sprite_ptr _sprite;
    bn::sprite_animate_action<2> _anim;
};

}

#endif