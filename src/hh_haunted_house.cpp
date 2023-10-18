#include "hh_haunted_house.h"

#include "bn_keypad.h"

#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_tmg_press_a.h"
#include "bn_regular_bg_items_tmg_you_lose.h"
#include "bn_regular_bg_items_tmg_you_win.h"
#include "bn_sprite_items_hh_eyes.h"
#include "bn_sprite_items_hh_monster.h"

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
    _bg(bn::regular_bg_items::tmg_press_a.create_bg((256 - 240) / 2, (256 - 160) / 2)),
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
    result.exit = data.pending_frames == 0;

    if(! _victory && ! _defeat)
    {
        // if(bn::keypad::a_pressed())
        // {
        //     _bg.set_item(bn::regular_bg_items::tmg_you_win);
        //     result.remove_title = true;
        //     _victory = true;
        // }
        // else if(! bn::keypad::start_pressed() && bn::keypad::any_pressed())
        // {
        //     _bg.set_item(bn::regular_bg_items::tmg_you_lose);
        //     result.remove_title = true;
        //     _defeat = true;
        // }
        _player.update();
        _monster.update();
        if(data.pending_frames == 0){
            _victory = true;
        }
    }
    else
    {
        if(_show_result_frames)
        {
            --_show_result_frames;
        }
        else
        {
            result.exit = true;
        }
    }

    return result;
}

void haunted_house::fade_out([[maybe_unused]] const mj::game_data& data)
{
}

player::player(bn::fixed x, bn::fixed y) : 
    _pos(x, y), 
    _sprite(bn::sprite_items::hh_eyes.create_sprite(x,y)) {
    
    _sprite.set_scale(2);
}

void player::update(){
    if(bn::keypad::up_held()){
        _pos.set_y(_pos.y() - 1);
    }
    if(bn::keypad::down_held()){
        _pos.set_y(_pos.y() + 1);
    }
    if(bn::keypad::left_held()){
        _pos.set_x(_pos.x() - 1);
    }
    if(bn::keypad::right_held()){
        _pos.set_x(_pos.x() + 1);
    }

    _sprite.set_position(_pos);
}

monster::monster(bn::fixed x, bn::fixed y) : 
    _pos(x, y),
    _sprite(bn::sprite_items::hh_monster.create_sprite(x,y)),
    _anim(bn::create_sprite_animate_action_forever(_sprite, 5, 
            bn::sprite_items::hh_monster.tiles_item(), 0, 1)) {
    
    _sprite.set_scale(2);
}

void monster::update(){
    _sprite.set_position(_pos);
    _anim.update();
}

}
