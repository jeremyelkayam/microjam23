
#include "hh_bat.h"

#include "bn_sprite_items_hh_monster.h"

namespace hh{

bat::bat(bn::fixed x, bn::fixed y) : 
    entity(x, y, 16, 16, 2, _left),
    _sprite(bn::sprite_items::hh_monster.create_sprite(x,y, 4)),
    _anim(bn::sprite_vertical_flip_toggle_action(_sprite, 5)),
    _turn_time(20),
    _timer(_turn_time) {    
    _sprite.set_scale(2);
}

void bat::update(){
    entity::update();
    _sprite.set_position(_pos);
    _anim.update();

    if(_timer == 0){
        _timer = _turn_time;
        _direction = (_direction + 1) % 8;
    }else{
        --_timer;
    }


}

}