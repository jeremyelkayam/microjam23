#ifndef HH_MONSTER_H
#define HH_MONSTER_H

#include "hh_entity.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"


namespace hh {
class monster : public entity {
public: 
    monster(bn::fixed x, bn::fixed y);
    void update();
    void point_at(bn::fixed_point pos);

private:
    bn::sprite_ptr _sprite;
    bn::sprite_animate_action<2> _anim;
};

}

#endif