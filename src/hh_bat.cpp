
#include "hh_bat.h"

#include "bn_sprite_items_hh_monster.h"

namespace hh{

bat::bat(bn::fixed x, bn::fixed y, uint8_t initial_direction, bn::fixed tempo, bn::random &rand) : 
    entity(x, y, 16, 16, bn::fixed(1.5) * tempo, initial_direction),
    _rand(rand),
    _tempo(tempo),
    _sprite(bn::sprite_items::hh_monster.create_sprite(x,y, 4)),
    _anim(bn::sprite_vertical_flip_toggle_action(_sprite, 5)),
    _turn_time(((bn::fixed(20) / tempo) * rand.get_fixed(0.75, 1.5)).round_integer()),
    _timer(_turn_time),
    _clockwise(_rand.get_int(2)) {    
}

void bat::update(const mj::game_data& data){
    entity::update(data);
    _sprite.set_position(_pos);
    _anim.update();

    //bouncing off walls logic. kinda jank
    if(_can_move && hitting_wall()){
        bounce_off_walls();
    //     _timer = _turn_time;
    //     int8_t turn_amount = _clockwise ? 2 : -2;
    //     _direction = (_direction + turn_amount) % 8;
    }

    if(_timer == 0){
        _timer = _turn_time;
        int8_t turn_amount = _clockwise ? 1 : -1;
        _direction = (_direction + turn_amount + 8) % 8;

        //every half circle, change the radius of the circle.
        // if(_direction % 4 == 0){
            // _turn_time = ((bn::fixed(20) / _tempo) * _rand.get_fixed(0.75, 1.5)).round_integer();
        // }
    }else{
        --_timer;
    }


}

void bat::lights_on(bn::random &rand){
    _sprite.set_item(bn::sprite_items::)
}

}