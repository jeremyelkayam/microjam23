#include "hh_haunted_house.h"

#include "bn_keypad.h"
#include "bn_log.h"

#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_hh_black_bg.h"
#include "bn_regular_bg_items_hh_gymnasium.h"
#include "bn_sprite_items_hh_monster.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_palettes.h"
#include "bn_sound_items.h"

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
    _player(0,0)
    // _spider(40, 40),
    // _bat(40,-40, 2),
    // _ghost(-40,-40,5)
{
    BN_LOG("total frames: ", _total_frames);
    BN_LOG("games done: ", completed_games);

    uint8_t first_baddie = data.random.get_int(3);
    uint8_t xquad = data.random.get_int(2) == 1 ? 1 : -1;
    uint8_t yquad = data.random.get_int(2) == 1 ? 1 : -1;
    bn::fixed xcor = data.random.get_fixed(20, 110) * xquad;
    bn::fixed ycor = yquad == 1 ? data.random.get_fixed(20, 75) : 
                                  data.random.get_fixed(-60, -20);
    uint8_t direction = data.random.get_int(8);
    if(first_baddie == 0){
        _spider.emplace(xcor, ycor);
    }else if(first_baddie == 1){
        _bat.emplace(xcor, ycor,direction);
    }else if(first_baddie == 2){
        _ghost.emplace(xcor, ycor,direction);
    }else{
        BN_ERROR("buddy you fucked up");
    }

}

void haunted_house::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

mj::game_result haunted_house::play(const mj::game_data& data)
{
    mj::game_result result;

    if(! _defeat)
    {

        _player.take_button_input();
        if(_spider){
            _spider->update();
            _spider->point_at(_player.pos());

        }
        if(_bat) _bat->update();
        if(_ghost) _ghost->update();

        if((_spider && _player.hitbox().intersects(_spider->hitbox())) || 
            (_bat && _player.hitbox().intersects(_bat->hitbox())) || 
            (_ghost && _player.hitbox().intersects(_ghost->hitbox()))){
            _defeat = true;
            result.remove_title = true;
            _player.disable_movement();
            bn::sound_items::hh_waves.play(1);
        }

        if(data.pending_frames == 90){
            //you won
            _victory = true;
            _player.show_body(data.random.get_int(2));
            _player.disable_movement();

            //todo: show guys holding up the baddies 
            if(_spider) _spider->disable_movement();
            if(_bat) _bat->disable_movement();
            if(_ghost) _ghost->disable_movement();


            bn::bg_palettes::set_brightness(1);
            bn::sprite_palettes::set_brightness(1);
        }
        if(data.pending_frames < 90 && data.pending_frames >= 60){
            bn::fixed brightness = bn::fixed(data.pending_frames - 60) * bn::fixed(0.033333);
            bn::bg_palettes::set_brightness(brightness);
            bn::sprite_palettes::set_brightness(brightness);
            _bg.set_item(bn::regular_bg_items::hh_gymnasium);
        }
    }
    else
    {
        //only happens if you lose
        if(_show_result_frames)
        {
            //todo: add pee-pants-ometer
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
