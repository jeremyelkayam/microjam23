
#include "hh_monster.h"

#include "bn_sprite_items_hh_monster.h"
#include "bn_math.h"

namespace hh{

monster::monster(bn::fixed x, bn::fixed y) : 
    entity(x, y, 16, 16, 0.5),
    _sprite(bn::sprite_items::hh_monster.create_sprite(x,y)),
    _anim(bn::create_sprite_animate_action_forever(_sprite, 5, 
            bn::sprite_items::hh_monster.tiles_item(), 0, 1)) {
    
    _sprite.set_scale(2);
}

void monster::update(){
    entity::update();
    _sprite.set_position(_pos);
    _anim.update();
}

void monster::point_at(bn::fixed_point pos){
    //this gives us the angle as a value between -0.5 and 0.5
    bn::fixed angle = bn::diamond_angle((pos.y() - _pos.y()).floor_integer(),
                                        (pos.x() - _pos.x()).floor_integer());

    //normalize it
    //scale it up to be within our 8 directions
    angle *= 8;
    //convert it back to my dumbass way of measuring these stupid things
    int8_t maybe_negative_dir = angle.round_integer();
    if(maybe_negative_dir < 0){
        _direction = 8 + maybe_negative_dir;
    }else {
        _direction= maybe_negative_dir;
    }

    // BN_LOG("angle: ", angle);
    // BN_LOG("direction of 8: ", _direction);
    
}

}