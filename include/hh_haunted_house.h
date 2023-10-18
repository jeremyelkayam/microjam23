#ifndef HH_HAUNTED_HOUSE_H
#define HH_HAUNTED_HOUSE_H

#include "bn_regular_bg_ptr.h"

#include "mj/mj_game.h"

namespace hh
{

class haunted_house : public mj::game
{

public:
    haunted_house(int completed_games, const mj::game_data& data);

    [[nodiscard]] bn::string<16> title() const final
    {
        return "$1,000,000!";
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
};

class player {
public: 
    player(bn::fixed x, bn::fixed y);
    void update();

private:
    bn::fixed_point _pos;
    bn::sprite_ptr _sprite;
}

}

#endif
