#ifndef HH_HAUNTED_HOUSE_H
#define HH_HAUNTED_HOUSE_H

#include "bn_regular_bg_ptr.h"
#include "bn_bg_palette_actions.h"
#include "bn_optional.h"
#include <bn_vector.h>

#include "hh_player.h"
#include "hh_bat.h"
#include "hh_spider.h"
#include "hh_ghost.h"

#include "mj/mj_game.h"


namespace hh
{

class explosion {
public:
    //fpc = frames per color
    explosion(bn::regular_bg_ptr &bg, uint8_t fpc);
    void update();
private:
    bn::regular_bg_ptr &_bg;
    bn::bg_palette_fade_to_action _fade;
    void reset_fade();
};

class haunted_house : public mj::game
{

public:
    haunted_house(int completed_games, const mj::game_data& data);

    [[nodiscard]] bn::string<16> title() const final
    {
        return "Avoid monsters!";
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
    bn::fixed _tempo;
    bn::regular_bg_ptr _bg;
    int _total_frames;
    int _show_result_frames = 120;
    bool _victory = false;
    bool _defeat = false;
    player _player;
    bn::optional<spider> _spider;
    bn::optional<bat> _bat;
    bn::optional<ghost> _ghost;
    bn::sprite_ptr _peepantsometer;
    bn::vector<bn::sprite_ptr, 14> _pee_bars;
    explosion _explosion;

    const uint8_t _normal = 4, _hard = 8; 
};


}

#endif
