#ifndef HH_PLAYER_H
#define HH_PLAYER_H

#include "bn_sprite_ptr.h"
#include "hh_entity.h"


namespace hh
{
class player : public entity {
public: 
    player(bn::fixed x, bn::fixed y);
    void update();
    void show_body();
    void take_button_input();
    void rotate_eyes();

private:
    bn::sprite_ptr _eyes, _body;
};

}

#endif
