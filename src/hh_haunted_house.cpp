#include "hh_haunted_house.h"

#include "bn_keypad.h"
#include "bn_log.h"

#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_hh_black_bg.h"
#include "bn_regular_bg_items_hh_gymnasium.h"
#include "bn_sprite_items_hh_peepantsometer.h"
#include "bn_sprite_items_hh_peebar.h"
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
    _blackbg(bn::regular_bg_items::hh_black_bg.create_bg((256 - 240) / 2, (256 - 160) / 2)),
    _room(bn::regular_bg_items::hh_gymnasium.create_bg((256 - 240) / 2, (256 - 160) / 2)),
    _total_frames(play_jingle(mj::game_jingle_type::METRONOME_16BEAT, completed_games, data)),
    _game_end_frame(_total_frames * 0.3),
    _lights_on_end_frame(_total_frames * 0.2),
    _tempo(recommended_music_tempo(completed_games, data)),
    _player(0,0, _tempo),
    _peepantsometer(bn::sprite_items::hh_peepantsometer.create_sprite(-90,30)),
    _explosion(_blackbg, 10)
{
    
    BN_LOG("tempo: ", _tempo);
    BN_LOG("total frames: ", _total_frames);
    BN_LOG("game end frame: ", _game_end_frame);
    BN_LOG("lights on end frame: ", _lights_on_end_frame);

    bn::rect_window::internal().set_bottom_right(0,0);
    bn::rect_window::internal().set_top_left(0,0);
    bn::rect_window::internal().set_show_all();
    bn::window::outside().set_show_bg(_room, false);

    //for the first enemy, only spawn spider or bat    
    spawn_enemy(data, data.random.get_int(0, 2));

    if(completed_games >= _normal){
        bool ghost = data.random.get_int(0, 2);
        if(ghost){
            spawn_enemy(data, 2);
        }else if(!_spider){
            spawn_enemy(data, 0);
        }else if(!_bat){
            spawn_enemy(data, 1);
        }
    }
    if(completed_games >= _hard && data.random.get_int(0, _very_hard) < completed_games){
        if(!_ghost){
            spawn_enemy(data, 2);
        }else if(!_spider){
            spawn_enemy(data, 0);
        }else if(!_bat){
            spawn_enemy(data, 1);
        }
    }


    _peepantsometer.set_scale(2);
    _peepantsometer.set_visible(false);
}

void haunted_house::spawn_enemy(const mj::game_data& data, uint8_t enemy_type){

    int8_t xquad = data.random.get_int(2) == 1 ? 1 : -1;
    int8_t yquad = data.random.get_int(2) == 1 ? 1 : -1;
    bn::fixed xcor = data.random.get_fixed(50, 110) * xquad;
    bn::fixed ycor = yquad == 1 ? data.random.get_fixed(20, 60) : 
                                  data.random.get_fixed(-75, -20);
    uint8_t direction = data.random.get_int(8);

    BN_LOG("first baddie xcor: ", xcor);
    BN_LOG("first baddie ycor: ", ycor);
    if(enemy_type == 0){
        BN_ASSERT(!_spider, "to spawn a spider you can't have one already");
        _spider.emplace(xcor, ycor, _tempo);
    }else if(enemy_type == 1){
        BN_ASSERT(!_bat, "to spawn a bat you can't have one already");
        _bat.emplace(xcor, ycor,direction, _tempo, data.random);
    }else if(enemy_type == 2){
        BN_ASSERT(!_ghost, "to spawn a ghost you can't have one already");

        //this block of code makes it so that the enemy is pointing at the player
        // ycor = _player.pos().y();
        // xcor = _player.pos().x();

        // if(direction == 7 || direction == 0 || direction == 1) xcor += 50;
        // if(direction == 1 || direction == 2 || direction == 3) ycor += 50;
        // if(direction == 3 || direction == 4 || direction == 5) xcor -= 50;
        // if(direction == 5 || direction == 6 || direction == 7) ycor -= 50;

        // //random variance
        // ycor += data.random.get_fixed(-10, 10);
        // xcor += data.random.get_fixed(-10, 10);        
        
        _ghost.emplace(xcor, ycor,direction, _tempo);
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

        if(data.pending_frames == _game_end_frame){
            //you won
            _victory = true;
            _player.disable_movement();

            //todo: show guys holding up the baddies 
            if(_spider) _spider->disable_movement();
            if(_bat) _bat->disable_movement();
            if(_ghost) _ghost->disable_movement();


            // bn::bg_palettes::set_brightness(1);
            // bn::sprite_palettes::set_brightness(1);
        }
        //todo: make this a fraction of total frames
        if(data.pending_frames < _game_end_frame && data.pending_frames >= _lights_on_end_frame){
            bn::fixed window_scale_factor = bn::fixed(_game_end_frame - data.pending_frames) / bn::fixed(_game_end_frame - _lights_on_end_frame);
            bn::rect_window iw = bn::rect_window::internal();
            iw.set_left(-120 * window_scale_factor);
            iw.set_right(120 * window_scale_factor);
            iw.set_top( - 80 * window_scale_factor);
            iw.set_bottom(80 * window_scale_factor);
            if(_player.hitbox().intersects(iw.boundaries())){
                //show your body when you are illuminated by the light ... 
                _player.show_body(data.random);
            }
        }
    }
    else
    {
        //only happens if you lose
        if(_show_result_frames)
        {
            if(!_peepantsometer.visible()){
                _peepantsometer.set_visible(true);
                if(_player.pos().x() <= _peepantsometer.x() + 30 && 
                   _player.pos().x() >= _peepantsometer.x() - 30){
                    _peepantsometer.set_x(-_peepantsometer.x());
                    BN_LOG("gotta move the peepantsometer");
                }
            }
            --_show_result_frames;
            if(_show_result_frames % 2 == 0){
                //rotate eyeballs every other frame
                _player.rotate_eyes();
            }

            //fill the peepantsometer every third frame
            if(!_pee_bars.full() && _show_result_frames % 3 == 0){
                bn::fixed xcor, ycor;
                if(_pee_bars.size() < 6){
                    xcor = _peepantsometer.x() - 12;
                    ycor = _peepantsometer.y() + 28 - (8 * _pee_bars.size());
                }else if(_pee_bars.size() < 12){
                    xcor = _peepantsometer.x() + 12;
                    ycor = _peepantsometer.y() + 28 - (8 * (_pee_bars.size() - 6));
                }else{
                    xcor = _peepantsometer.x();
                    ycor = _peepantsometer.y() + 28 - (8 * (_pee_bars.size() - 8));
                }
                _pee_bars.emplace_back(bn::sprite_items::hh_peebar.create_sprite(xcor, ycor));
                _pee_bars.back().set_scale(2);
            }
            _explosion.update();


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

explosion::explosion(bn::regular_bg_ptr &bg, uint8_t fpc) : 
    _blackbg(bg),
    _fade(bn::bg_palette_fade_to_action(bg.palette(), fpc, 1)){
        //can probably do this with palette rotation actually

    bn::bg_palette_ptr palette = _blackbg.palette();
    palette.set_rotate_count(-1);
    
    reset_fade();
}

void explosion::update(){
    _fade.update();
    if(_fade.done()){
        reset_fade();
    }
}

//this fades between the 16 colors in the bg palette as it simultaneously rotates 
//between them.. basically giving us an atari explosion effect
void explosion::reset_fade(){
    bn::bg_palette_ptr palette = _blackbg.palette();
    BN_LOG("colors count for palette: ", palette.colors_count());
    uint8_t next_rotation = (palette.rotate_count() + 1) % palette.colors_count();
    uint8_t next_fade = palette.colors_count() - (next_rotation + 1);
    palette.set_fade_intensity(0);
    palette.set_fade_color(palette.colors().at(next_fade));
    palette.set_rotate_count(next_rotation);

    _fade.reset();
}

}
