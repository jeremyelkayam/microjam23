#include "hh_haunted_house.h"

#include "bn_keypad.h"
#include "bn_log.h"

#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_hh_black_bg.h"
#include "bn_regular_bg_items_hh_gymnasium.h"
#include "bn_sprite_items_hh_monster.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_palettes.h"

namespace
{
    constexpr bn::string_view code_credits[] = { "Jeremy Elkayam, Michael Elkayam" };
    constexpr bn::string_view graphics_credits[] = { "Jeremy Elkayam, Michael Elkayam" };
}

MJ_GAME_LIST_ADD(hh::haunted_house)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
// MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
// MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace hh
{

haunted_house::haunted_house(int completed_games, const mj::game_data& data) :
    _bg(bn::regular_bg_items::hh_black_bg.create_bg((256 - 240) / 2, (256 - 160) / 2)),
    _total_frames(play_jingle(mj::game_jingle_type::METRONOME_16BEAT, completed_games, data)),
    _player(0,0),
    _monster(40, 40)
{
}

void haunted_house::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

mj::game_result haunted_house::play(const mj::game_data& data)
{
    mj::game_result result;

    // if(data.pending_frames == 180) {
        // _defeat = true;
        //     result.remove_title = true;

    // }

    if(data.pending_frames == 90){
        //you won
        _victory = true;
        _player.show_body();
        bn::bg_palettes::set_brightness(1);
        bn::sprite_palettes::set_brightness(1);
    }
    if(data.pending_frames < 90 && data.pending_frames >= 60){
        bn::fixed brightness = bn::fixed(data.pending_frames - 60) * bn::fixed(0.033333);
        bn::bg_palettes::set_brightness(brightness);
        bn::sprite_palettes::set_brightness(brightness);
        _bg.set_item(bn::regular_bg_items::hh_gymnasium);
    }
// ! _victory && 
    if(! _defeat)
    {

        // if collision with monster
        //     result.remove_title = true;
        //     _defeat = true;
        _player.take_button_input();
        _monster.update();
    }
    else
    {
        //only happens if you lose
        if(_show_result_frames)
        {
            --_show_result_frames;
            if(_show_result_frames % 2 == 0){
                //rotate eyeballs every other frame
                _player.rotate_eyes();
            }
        }
        else
        {
            result.exit = true;
        }
    }

    _player.update();


    return result;
}

void haunted_house::fade_out([[maybe_unused]] const mj::game_data& data)
{
}

}
