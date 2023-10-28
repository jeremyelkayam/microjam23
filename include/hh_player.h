#ifndef HH_PLAYER_H
#define HH_PLAYER_H

#include "bn_sprite_ptr.h"
#include "hh_entity.h"
#include "bn_random.h"


namespace hh
{
class player : public entity {
public: 
    player(bn::fixed x, bn::fixed y, bn::fixed tempo);
    void update();
    void show_body(bn::random &rand);
    void take_button_input();
    void rotate_eyes();

private:
    bn::sprite_ptr _eyes, _body;
};

}

#endif
