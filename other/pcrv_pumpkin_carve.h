#ifndef PCRV_PUMPKIN_CARVE_H
#define PCRV_PUMPKIN_CARVE_H

#include "bn_regular_bg_ptr.h"
#include "bn_bg_palette_actions.h"
#include "bn_optional.h"
#include "bn_rect_window.h"
#include "bn_rect_window_actions.h"
#include "bn_blending.h"
#include "bn_vector.h"
#include "bn_sound.h"

#include "mj/mj_game.h"


namespace pcrv
{
class pumpkin_carve : public mj::game
{

public:
    pumpkin_carve(int completed_games, const mj::game_data& data);

    [[nodiscard]] bn::string<16> title() const final
    {
        return "Carve!";
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

    void spawn_enemy();

private:
    bn::regular_bg_ptr _pumpkin, _bg;
    bn::affine_bg_ptr _bigg_nife;
    bn::fixed _tempo;
    int _total_frames;
    int _show_result_frames = 120;
    bool _victory = false;
    bool _defeat = false;
    mj::difficulty_level _difficulty_level;
};


}

#endif
