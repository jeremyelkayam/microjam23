#include "hh_player.h"
#include "bn_keypad.h"
#include "bn_sprite_items_hh_eyes.h"
#include "bn_sprite_items_hh_person_32.h"
#include "bn_sprite_items_hh_ken.h"

namespace hh 
{

player::player(bn::fixed x, bn::fixed y, bn::fixed tempo) : 
    entity(x, y, 14, 2, bn::fixed(1) * tempo, 0),
    _eyes(bn::sprite_items::hh_eyes.create_sprite(x,y)),
    _body(bn::sprite_items::hh_person_32.create_sprite(x,y)) {
    

    _eyes.set_scale(2);
    _body.set_visible(false);
    _body.set_z_order(10);
}


void player::update(){
    entity::update();

    //this is dumb and stupid and could be done in way less code but 
    //i dont want to fix it lol !!! 
    switch(_direction){
        case 0:
            _eyes.set_item(bn::sprite_items::hh_eyes, 1);
            _eyes.set_horizontal_flip(false);
            _eyes.set_vertical_flip(false);
            break;
        case 1:
            _eyes.set_item(bn::sprite_items::hh_eyes, 2);
            _eyes.set_horizontal_flip(false);
            _eyes.set_vertical_flip(false);
            break;
        case 2:
            _eyes.set_item(bn::sprite_items::hh_eyes, 3);
            _eyes.set_horizontal_flip(false);
            _eyes.set_vertical_flip(false);
            break;
        case 3:
            _eyes.set_item(bn::sprite_items::hh_eyes, 2);
            _eyes.set_horizontal_flip(true);
            _eyes.set_vertical_flip(false);
            break;
        case 4:
            _eyes.set_item(bn::sprite_items::hh_eyes, 1);
            _eyes.set_horizontal_flip(true);
            _eyes.set_vertical_flip(false);
            break;
        case 5:
            _eyes.set_item(bn::sprite_items::hh_eyes, 2);
            _eyes.set_horizontal_flip(true);
            _eyes.set_vertical_flip(true);
            break;
        case 6:
            _eyes.set_item(bn::sprite_items::hh_eyes, 3);
            _eyes.set_horizontal_flip(false);
            _eyes.set_vertical_flip(true);
            break;
        case 7:
            _eyes.set_item(bn::sprite_items::hh_eyes, 2);
            _eyes.set_horizontal_flip(false);
            _eyes.set_vertical_flip(true);
            break;
        case 8:
            _eyes.set_item(bn::sprite_items::hh_eyes, 0);
            break;
        default:
            BN_ERROR("invalid direction found for player (must be between 0 and 8): ", _direction);
    }

    _eyes.set_position(_pos);

    //annoying and stupid graphical adjustments .... 
    if(_eyes.vertical_flip()){
        _eyes.set_y(_pos.y() - 3);
    }
    if(_eyes.horizontal_flip()){
        _eyes.set_x(_pos.x() - 1);
    }
}

void player::show_body(bn::random &rand){
    _body.set_x(_pos.x());
    _body.set_y(_pos.y() + 6);
    _body.set_visible(true);
    uint8_t costume = rand.get_int(2);
    if(costume == 1){
        _body.set_item(bn::sprite_items::hh_ken);
    }
}

void player::take_button_input(){

    if(!bn::keypad::up_held() && !bn::keypad::down_held() && !bn::keypad::left_held() && !bn::keypad::right_held()){
        _direction = 8;
    }
    if(bn::keypad::right_held()){
        _direction = 0;
    }
    if(bn::keypad::down_held()){
        _direction = 2;
    }
    if(bn::keypad::up_held()){
        _direction = 6;
    }    
    if(bn::keypad::left_held()){
        _direction = 4;
    }
    if(bn::keypad::right_held() && bn::keypad::down_held()){
        _direction = 1;
    }
    if(bn::keypad::down_held() && bn::keypad::left_held()){
        _direction = 3;
    }
    if(bn::keypad::left_held() && bn::keypad::up_held()){
        _direction = 5;
    }

    if(bn::keypad::up_held() && bn::keypad::right_held()){
        _direction = 7;
    }    
}

void player::rotate_eyes(){
    _direction = (_direction + 1) % 8;
}

}