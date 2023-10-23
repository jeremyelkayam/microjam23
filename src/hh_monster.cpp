
#include "hh_monster.h"

#include "bn_sprite_items_hh_monster.h"

namespace hh{

monster::monster(bn::fixed x, bn::fixed y) : 
    _pos(x, y),
    _sprite(bn::sprite_items::hh_monster.create_sprite(x,y)),
    _anim(bn::create_sprite_animate_action_forever(_sprite, 5, 
            bn::sprite_items::hh_monster.tiles_item(), 0, 1)) {
    
    _sprite.set_scale(2);
}

void monster::update(){
    _sprite.set_position(_pos);
    _anim.update();
}

}