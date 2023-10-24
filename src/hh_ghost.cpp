
#include "hh_ghost.h"

#include "bn_sprite_items_hh_monster.h"
#include "bn_math.h"

namespace hh{

ghost::ghost(bn::fixed x, bn::fixed y, uint8_t initial_direction) : 
    entity(x, y, 16, 16, 2, initial_direction),
    _sprite(bn::sprite_items::hh_monster.create_sprite(x,y,2)),
    _anim(bn::create_sprite_animate_action_forever(_sprite, 5, 
            bn::sprite_items::hh_monster.tiles_item(), 3, 2)) {
    
    _sprite.set_scale(2);
}

void ghost::update(){

    if(_pos.y() >= _bbound - 5 || _pos.y() <= _tbound + 5 || 
       _pos.x() >= _rbound - 5 || _pos.x() <= _lbound + 5){
        //mirror the direction so it bounces off the walls
        _direction = (_direction + 4) % 8;
        BN_LOG("direction:", _direction);
    }

    entity::update();
    _sprite.set_position(_pos);
    _anim.update();

    if(2 <= _direction && _direction < 6){
        _sprite.set_horizontal_flip(false);
    }else{
        _sprite.set_horizontal_flip(true);
    }
}


}