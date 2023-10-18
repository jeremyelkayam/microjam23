#ifndef HH_HAUNTED_HOUSE_H
#define HH_HAUNTED_HOUSE_H

#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game.h"


namespace hh
{
class player {
public: 
    player(bn::fixed x, bn::fixed y);
    void update();

private:
    bn::fixed_point _pos;
    bn::sprite_ptr _sprite;
};

class monster {
public: 
    monster(bn::fixed x, bn::fixed y);
    void update();

private:
    bn::fixed_point _pos;
    bn::sprite_ptr _sprite;
    bn::sprite_animate_action<2> _anim;
};

class haunted_house : public mj::game
{

public:
    haunted_house(int completed_games, const mj::game_data& data);

    [[nodiscard]] bn::string<16> title() const final
    {
        return "Survive!";
    }

    [[nodiscard]] int total_frames() const final
    {
        return _total_frames;
    }

    void fade_in(const mj::game_data& data) final;

    [[nodiscard]] mj::game_result play(const mj::game_data& data) final;

    [[nodiscard]] bool victory() const final
    {
        return _victory;
    }

    void fade_out(const mj::game_data& data) final;

private:
    bn::regular_bg_ptr _bg;
    int _total_frames;
    int _show_result_frames = 60;
    bool _victory = false;
    bool _defeat = false;
    player _player;
    monster _monster;
};

}

#endif
