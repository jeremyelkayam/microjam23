#include "hh_entity.h"

namespace hh {

entity::entity(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height, bn::fixed speed, uint8_t direction) : 
    _pos(x, y), 
    _hitbox(x, y, width, height),
    _speed(speed),
    _direction(direction),
    _can_move(true) {
    // BN_LOG("speed of entity: ", _speed);
}

void entity::update(){
    //if your direction is center, you are not moving


    if(_can_move && _direction != _center){
        bn::fixed dx = _speed, dy = _speed;
        if(_direction % 2 == 1){
            //if direction is odd, we are going diagonally
            dx *= _ds;
            dy *= _ds;
        }else if(_direction % 4 == 0){
            //multiples of 4 are left and right. this means no y-component
            dy = 0;
        }else if(_direction % 4 == 2){
            //this gives us the other two cardinal directions, up and down
            //these have no x-component
            dx = 0;
        }

        //directions between 3 (down left) and 5 are negative in the x direction
        if(_down_left <= _direction && _direction <= _up_left){
            dx *= -1;
        }

        //directions between 5 and 7 are negative in the y direction
        if(_up_left <= _direction && _direction <= _up_right){
            dy *= -1;
        }

        if(_pos.x() + dx > _rbound || _pos.x() + dx < _lbound){
            dx = 0;
        } 
        if(_pos.y() + dy > _bbound || _pos.y() + dy < _tbound){
            dy = 0;
        } 

        _pos.set_x(_pos.x() + dx);
        _pos.set_y(_pos.y() + dy);
        _hitbox.set_position(_pos);
    }

}

}